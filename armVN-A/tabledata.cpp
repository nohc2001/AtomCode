#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

constexpr char filename[256] = "tabledata_example.txt";
constexpr char outfile[256] = "tableout.txt";

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

struct ArmDecodeLink{
    char** mask;
    void* next_table_ptr;
};

struct ArmDecodeTable{
    char table_name[128];
    unsigned int oprange_count;
    unsigned int link_count;
    op_range* oprangeArr;
    ArmDecodeLink* linkArr;
};

int decode_table_count = 0;
ArmDecodeTable* tables[1024] = {};

void PushNewTable(){
    tables[decode_table_count] = (ArmDecodeTable*)malloc(sizeof(ArmDecodeTable));
    decode_table_count += 1;
}

void ReadDecodingTables(){
    ifstream rs;
    rs.open(filename);

    char c = 0;
    rs >> c;
    if(c == '#'){
        //table adding
        PushNewTable();
        while(true){
            rs >> c;
            int tnindex = 0;
            if(c != '\n'){
                tables[decode_table_count]->table_name[tnindex] = c;
                tnindex += 1;
            }
            else{
                tables[decode_table_count]->table_name[tnindex] = 0;
                tnindex += 1;
                break;
            }
        }

        char* tablename = tables[decode_table_count]->table_name;
        for(int i=0;i<decode_table_count;++i){
            for(int k=0;k<tables[decode_table_count]->link_count;++k){
                if(strcmp((char*)tables[decode_table_count]->linkArr[i].next_table_ptr, tablename) == 0){
                    free(tables[decode_table_count]->linkArr[i].next_table_ptr);
                    tables[decode_table_count]->linkArr[i].next_table_ptr = nullptr;
                    tables[decode_table_count]->linkArr[i].next_table_ptr = (void*)tables[decode_table_count];
                }
            }
        }
        
        rs >> tables[decode_table_count]->oprange_count;
        rs >> tables[decode_table_count]->link_count;
        tables[decode_table_count]->oprangeArr = (op_range*)malloc(sizeof(op_range)* tables[decode_table_count]->oprange_count);
        for(int i=0;i<tables[decode_table_count]->oprange_count;++i){
            rs >> tables[decode_table_count]->oprangeArr[i].start;
            rs >> tables[decode_table_count]->oprangeArr[i].end;
        }

        tables[decode_table_count]->linkArr = (ArmDecodeLink*)malloc(sizeof(ArmDecodeLink)*tables[decode_table_count]->link_count);
        for(int i=0;i<tables[decode_table_count]->link_count;++i){
            tables[decode_table_count]->linkArr[i].mask = (char**)malloc(sizeof(char*)*tables[decode_table_count]->oprange_count);
            for(int k=0;k<tables[decode_table_count]->oprange_count;++k){
                int oplen = tables[decode_table_count]->oprangeArr[k].end - tables[decode_table_count]->oprangeArr[k].start + 1;
                tables[decode_table_count]->linkArr[i].mask[i] = (char *)malloc(oplen + 1);
                rs >> tables[decode_table_count]->linkArr[i].mask[i];
            }
            tables[decode_table_count]->linkArr[i].next_table_ptr = malloc(128);
            rs >> c;

            char* cstr = (char*)tables[decode_table_count]->linkArr[i].next_table_ptr;
            while (true)
            {
                rs >> c;
                int tnindex = 0;
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

void Arm_DecodingMachineCodeToASM(uint32_t instruction){
    mainInst = instruction;
    ArmDecodeTable* table = tables[0];
    bool hit = false;
    for(int i=0;i<table->link_count;++i){
        for(int k=0;k<table->oprange_count;++k){
            hit = hit & masking(table->oprangeArr[k], table->linkArr[i].mask[k]);
        }
        if(hit){
            table = (ArmDecodeTable*)table->linkArr[i].next_table_ptr;
            break;
            // 하지만 포인터가 문자열일때 감지할 수 없음. 추가적인 부분을 만들 필요가 있다.
        }
    }
}

int main(){
    
    return 0;
}