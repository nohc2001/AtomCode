#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

constexpr char filename[256] = "tabledata_example.txt";
constexpr char outfile[256] = "tableout.txt";
constexpr char instfile[256] = "all_inst.txt";

uint32_t mainInst;

inline bool is1(uint32_t loc)
{
  return mainInst & (1 << loc);
}

struct op_range
{
  int start = 0;
  int end = 0;
};

inline int gr(op_range r, int index)
{
  return r.end - index;
}

bool masking(op_range r, const char *mask)
{
  if (mask[0] == '!' && mask[1] == '=')
  {
    bool b = true;
    int len = 1 + r.end - r.start;
    for (int i = 2; i < len; ++i)
    {
      switch (mask[i])
      {
      case '1':
        b = b && is1(gr(r, i-2));
        break;
      case '0':
        b = b && !is1(gr(r, i-2));
        break;
      case '>':
        return b;
      }

      if (b == false)
        return true;
      else
        return false;
    }
  }
  if (mask[0] == '-')
    return true;
  int len = 1 + r.end - r.start;

  if (len > 2 && (mask[0] == '!' && mask[1] == '='))
  {
    // diff mod.
    return !masking(r, &mask[2]);
  }

  bool b = true;
  for (int i = 0; i < len; ++i)
  {
    switch (mask[i])
    {
    case '1':
      b = b && is1(gr(r, i));
      break;
    case '0':
      b = b && !is1(gr(r, i));
      break;
    case '>':
      return b;
    }

    if (b == false)
      return false;
  }

  return true;
}

bool isp(int loc, char bit)
{
  switch (bit)
  {
  case '1':
    return is1(loc);
  }
  return !is1(loc);
}

struct ArmDecodeLink
{
  char **mask;
  void *next_table_ptr;
};

// parant table ptr 으로 역으로도 갈 수 있게 하자.
// oprange를 통해 4바이트에 비트를 박는 식. (확정된 0과 1만 새김.)
struct ArmDecodeTable
{
  unsigned int oprange_count;
  unsigned int link_count;
  char table_name[128];
  op_range *oprangeArr;
  ArmDecodeLink *linkArr;
};

struct InstructionMask{
  uint32_t opcode_0mask;
  uint32_t opcode_1mask;
  uint32_t imm_0mask;
  uint32_t imm_1mask;
  uint32_t reg0_0mask;
  uint32_t reg0_1mask;
  uint32_t disp_0mask;
  uint32_t dsip_1mask;
  //...
};

int decode_table_count = 0;
ArmDecodeTable *tables[1024] = {};
#define last_table tables[decode_table_count - 1]

void PushNewTable()
{
  tables[decode_table_count] = (ArmDecodeTable *)malloc(sizeof(ArmDecodeTable));
  decode_table_count += 1;
}

unsigned int opIndexWeight[32] = {};
unsigned int opIndexPriority[32] = {};

void ReadDecodingTables()
{
  ifstream rs;
  rs.open(filename);

  while (!rs.eof())
  {
    char c = 0;
    c = rs.get();
    if (c == '#')
    {
      // table adding
      int tnindex = 0;
      PushNewTable();
      last_table->table_name[tnindex] = '#';
      tnindex += 1;
      while (true)
      {
        c = rs.get();

        if (c != '\n')
        {
          last_table->table_name[tnindex] = c;
          tnindex += 1;
        }
        else
        {
          last_table->table_name[tnindex] = 0;
          tnindex += 1;
          break;
        }
      }

      char *tablename = last_table->table_name;
      /*
      for (int i = 0; i < decode_table_count; ++i)
      {
        for (int k = 0; k < tables[i]->link_count; ++k)
        {
          if (strcmp((char *)tables[i]->linkArr[k].next_table_ptr, tablename) == 0)
          {
            free(tables[i]->linkArr[k].next_table_ptr);
            tables[i]->linkArr[k].next_table_ptr = nullptr;
            tables[i]->linkArr[k].next_table_ptr = (void *)last_table;
          }
        }
      }
      */

      rs >> last_table->oprange_count;
      rs >> last_table->link_count;
      last_table->oprangeArr = (op_range *)malloc(sizeof(op_range) * last_table->oprange_count);
      for (int i = 0; i < last_table->oprange_count; ++i)
      {
        rs >> last_table->oprangeArr[i].start;
        rs >> last_table->oprangeArr[i].end;

        for(int k=last_table->oprangeArr[i].start;k<=last_table->oprangeArr[i].end;++k){
          opIndexWeight[k] += 1;
        }
      }

      last_table->linkArr = (ArmDecodeLink *)malloc(sizeof(ArmDecodeLink) * last_table->link_count);
      for (int i = 0; i < last_table->link_count; ++i)
      {
        last_table->linkArr[i].mask = (char **)malloc(sizeof(char *) * last_table->oprange_count);
        for (int k = 0; k < last_table->oprange_count; ++k)
        {
          int oplen = last_table->oprangeArr[k].end - last_table->oprangeArr[k].start + 1;
          last_table->linkArr[i].mask[k] = (char *)malloc(oplen + 1);
          rs >> last_table->linkArr[i].mask[k];
        }
        last_table->linkArr[i].next_table_ptr = malloc(128);
        c = rs.get();
        int tnindex = 0;
        char *cstr = (char *)last_table->linkArr[i].next_table_ptr;
        cstr[0] = '#';
        tnindex += 1;
        while (true)
        {
          c = rs.get();
          if (c != '\n')
          {
            cstr[tnindex] = c;
            tnindex += 1;
          }
          else
          {
            cstr[tnindex] = 0;
            tnindex += 1;
            break;
          }
        }
      }
    }
  }

  for(int i=0;i<decode_table_count;++i){
    ArmDecodeTable* t0 = tables[i];
    for(int k=0;k<t0->link_count;++k){
      bool istable = false;
      char* cstr0 = (char*)t0->linkArr[k].next_table_ptr;
      for(int u=0;u<decode_table_count;++u){
        ArmDecodeTable* t1 = tables[u];
        if(strcmp(t1->table_name, cstr0) == 0){
          free(cstr0);
          t0->linkArr[k].next_table_ptr = (void*)t1;
          istable = true;
          break;
        }
      }

      if((istable == false && cstr0[1] == 'S') && ('M' == cstr0[2] && cstr0[3] == 'E')){
        cout << "in table " << t0->table_name << " sus link.. : " << cstr0 << endl;
      }
      if((istable == false && cstr0[1] == 'S') && ('V' == cstr0[2] && cstr0[3] == 'E')){
        cout << "in table " << t0->table_name << " sus link.. : " << cstr0 << endl;
      }
    }
  }
}

void Arm_DecodingMachineCodeToASM(uint32_t instruction)
{
  mainInst = instruction;
  ArmDecodeTable *table = tables[0];
  bool hit = true;
  for (int i = 0; i < table->link_count; ++i)
  {
    hit = true;
    for (int k = 0; k < table->oprange_count; ++k)
    {
      hit = hit & masking(table->oprangeArr[k], table->linkArr[i].mask[k]);
    }
    if (hit)
    {
      char *cstr = (char *)table->linkArr[i].next_table_ptr;
      if (cstr[0] == '#')
      {
        if(strcmp(cstr, "#Unallocated.") == 0){
          break;
        }
        cout << cstr << endl;
        break;
      }
      else
      {
        table = (ArmDecodeTable *)table->linkArr[i].next_table_ptr;
      }
    }
  }
}

void TableShow()
{
  for (int i = 0; i < decode_table_count; ++i)
  {
    cout << "table name : " << tables[i]->table_name << endl;
    cout << "table_oprange_count : " << tables[i]->oprange_count << endl;
    for (int k = 0; k < tables[i]->oprange_count; ++k)
    {
      cout << "oprange[" << k << "] : (" << tables[i]->oprangeArr[k].start << ", " << tables[i]->oprangeArr[k].end << ")" << endl;
    }
    cout << "table_link_count : " << tables[i]->link_count << endl;
    for (int k = 0; k < tables[i]->link_count; ++k)
    {
      char *cstr = (char *)tables[i]->linkArr[k].next_table_ptr;
      if (cstr[0] == '#')
      {
        cout << "link[" << k << "]_instruction : " << cstr << endl;
      }
      else
      {
        ArmDecodeTable *t = (ArmDecodeTable *)tables[i]->linkArr[k].next_table_ptr;
        cout << "link[" << k << "]_table : " << t->table_name << endl;
      }
    }
  }
}

void InstShow()
{
  ofstream out;
  out.open(instfile);

  for (int i = 0; i < decode_table_count; ++i)
  {
    for (int k = 0; k < tables[i]->link_count; ++k)
    {
      char *cstr = (char *)tables[i]->linkArr[k].next_table_ptr;
      if(strcmp(cstr, "#Unallocated.")==0)
      {
        continue;
      }
      if (cstr[0] == '#')
      {
        out << cstr << endl;
      }
    }
  }

  out.close();
}

int main()
{
  ReadDecodingTables();
  for(int i=0;i<32;++i){
    opIndexPriority[i] = i;
  }
  for(int i=0;i<32;++i){
    for(int k=i+1;k<32;++k){
      if(opIndexWeight[i] > opIndexWeight[k]){
        unsigned int temp = 0;
        temp = opIndexWeight[i];
        opIndexWeight[i] = opIndexWeight[k];
        opIndexWeight[k] = temp;

        temp = opIndexPriority[i];
        opIndexPriority[i] = opIndexPriority[k];
        opIndexPriority[k] = temp;
      }
    }
  }
  InstShow();
  uint32_t priority = 0;
  uint32_t inst = 1;
  while (priority != -1)
  {
    inst = 0;
    for(int i=0;i<32;i+=8){
      inst |= ((priority>>i) & 1) << opIndexPriority[i];
      inst |= ((priority>>(i+1)) & 1) << opIndexPriority[i+1];
      inst |= ((priority>>(i+2)) & 1) << opIndexPriority[i+2];
      inst |= ((priority>>(i+3)) & 1) << opIndexPriority[i+3];
      inst |= ((priority>>(i+4)) & 1) << opIndexPriority[i+4];
      inst |= ((priority>>(i+5)) & 1) << opIndexPriority[i+5];
      inst |= ((priority>>(i+6)) & 1) << opIndexPriority[i+6];
      inst |= ((priority>>(i+7)) & 1) << opIndexPriority[i+7];
    }
    Arm_DecodingMachineCodeToASM(inst);
    priority += 1;
  }
  return 0;
}