#ifndef _UTLI_MY_H_
#define _UTLI_MY_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

// #define START_FILE_NO 1
// #define END_FILE_NO 10
int startFileNo = 1;
int endFileNo = 10;
int totMemInKBytes = 600;


struct FIVE_TUPLE{	char key[13];	};
typedef vector<FIVE_TUPLE> TRACE;
// TRACE traces[END_FILE_NO - START_FILE_NO + 1];
TRACE traces[10];

// 处理命令行参数的函数
void processCommandLine(int argc, char *argv[]) {
    // 检查是否有足够的参数
    if (argc != 5) {
        fprintf(stderr, "Usage: %s -m <memory_size_in_bytes> -s <start_value> -e <endFileNo>\n", argv[0]);
        exit(1);
    }

    // 处理命令行参数
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-m") == 0) {
            // 获取内存大小参数并将其转换为整数
            totMemInKBytes = atoi(argv[i + 1]);
            printf("TOT_MEM_IN_KBYTES: %dB\n", totMemInKBytes);
        } else if (strcmp(argv[i], "-s") == 0) {
            // 获取 -s 参数并将其转换为整数
            startFileNo = atoi(argv[i + 1]);
            printf("Start File Number: %d\n", startFileNo);
        } else if (strcmp(argv[i], "-e") == 0) {
            // 获取 -e 参数并将其转换为整数
            endFileNo = atoi(argv[i + 1]);
            printf("End File Number: %d\n", endFileNo);
        } else {
            fprintf(stderr, "Invalid option: %s\n", argv[i]);
            exit(1);
        }
    }
}

void ReadInTraces(const char *trace_prefix)
{
	for(int datafileCnt = startFileNo; datafileCnt <= endFileNo; ++datafileCnt)
	{
		char datafileName[100];
		sprintf(datafileName, "%s%d.dat", trace_prefix, datafileCnt - 1);
		FILE *fin = fopen(datafileName, "rb");

		FIVE_TUPLE tmp_five_tuple;
		traces[datafileCnt - 1].clear();
		while(fread(&tmp_five_tuple, 1, 13, fin) == 13)
		{
			traces[datafileCnt - 1].push_back(tmp_five_tuple);
		}
		fclose(fin);

		printf("Successfully read in %s, %ld packets\n", datafileName, traces[datafileCnt - 1].size());
	}
	printf("\n");
}

#endif