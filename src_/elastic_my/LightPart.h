#ifndef _LIGHT_PART_MY_H_
#define _LIGHT_PART_MY_H_

#include "../common/EMFSD.h"
#include "param.h"

template<int init_mem_in_bytes>
class LightPart
{
	static constexpr int counter_num = init_mem_in_bytes;
	BOBHash32 *bobhash = NULL;

public:
	uint8_t counters[counter_num];
	int mice_dist[256];
	EMFSD *em_fsd_algo = NULL;

	LightPart()
	{
		clear();
		std::random_device rd;
       	bobhash = new BOBHash32(rd() % MAX_PRIME32);
	}
	~LightPart()
	{
		delete bobhash;
	}

	void clear()
	{
		memset(counters, 0, counter_num);
		memset(mice_dist, 0, sizeof(int) * 256);
	}


/* insertion */
	void insert(uint8_t *key, int f = 1)
	{
		uint32_t hash_val = (uint32_t)bobhash->run((const char*)key, KEY_LENGTH_4);
		uint32_t pos = hash_val % (uint32_t)counter_num;

		int old_val = (int)counters[pos];
        int new_val = (int)counters[pos] + f;

        new_val = new_val < 255 ? new_val : 255;
        counters[pos] = (uint8_t)new_val;

        mice_dist[old_val]--;
        mice_dist[new_val]++;
	}

	void swap_insert(uint8_t *key, int f)
	{
		uint32_t hash_val = (uint32_t)bobhash->run((const char*)key, KEY_LENGTH_4);
        uint32_t pos = hash_val % (uint32_t)counter_num;

        f = f < 255 ? f : 255;
        if (counters[pos] < f) 
        {
            int old_val = (int)counters[pos];
            counters[pos] = (uint8_t)f;
            int new_val = (int)counters[pos];

			mice_dist[old_val]--;
			mice_dist[new_val]++;
		}
	}


/* query */
	int query(uint8_t *key) 
	{
        uint32_t hash_val = (uint32_t)bobhash->run((const char*)key, KEY_LENGTH_4);
        uint32_t pos = hash_val % (uint32_t)counter_num;

        return (int)counters[pos];
    }
};

#endif