#ifndef _HEAVYPART_MY_H_
#define _HEAVYPART_MY_H_

#include "param.h"

template<int bucket_num>
class HeavyPart
{
public:
	alignas(64) Bucket buckets[bucket_num];

	HeavyPart()
	{
		clear();
	}
	~HeavyPart(){}

	void clear()
	{
		memset(buckets, 0, sizeof(Bucket) * bucket_num);
	}

/* insertion */
	int insert(uint8_t *key, uint8_t *swap_key, uint32_t &swap_val, uint32_t f = 1)
	{
		uint32_t fp; // key : 4B, hash result fingerprint
		int pos = CalculateFP(key, fp); // key : 13B, IP 5-tuple; pos : i-th bucket, then check 7 valid counter

		/* find if there has matched counter in the bucket */
		int matched = -1, empty = -1, min_counter = 0;
		uint32_t min_counter_val = GetCounterVal(buckets[pos].val[0]); // min counter may be evicted (mice flows) to light part
		for(int i = 0; i < COUNTER_PER_BUCKET - 1; i++) // i can be uint8_t, MAX_VALID_COUNTER can replace COUNTER_PER_BUCKET - 1
		{
			if(buckets[pos].key[i] == fp){
				matched = i;
				break;
			}
			if(buckets[pos].key[i] == 0 && empty == -1) // key always isn't 0?
				empty = i; //? why not break?
			if(min_counter_val > GetCounterVal(buckets[pos].val[i])){
				min_counter = i;
				min_counter_val = GetCounterVal(buckets[pos].val[i]);
			}
		}

		/* if matched */
		if(matched != -1){
			buckets[pos].val[matched] += f;
			return 0;
		}

		/* if there has empty bucket */
		if(empty != -1){
			buckets[pos].key[empty] = fp;
			buckets[pos].val[empty] = f; // flag is False as the counter is empty
			return 0;
		}

		/* update guard val(vote-) and comparison */
		uint32_t guard_val = buckets[pos].val[MAX_VALID_COUNTER];
		guard_val = UPDATE_GUARD_VAL(guard_val); // ? why not add f?

		if(!JUDGE_IF_SWAP(GetCounterVal(min_counter_val), guard_val))
		{
			buckets[pos].val[MAX_VALID_COUNTER] = guard_val;
			return 2; // not evicted
		} // else {}

		// evicted
		*((uint32_t*)swap_key) = buckets[pos].key[min_counter]; // evicted key
		swap_val = buckets[pos].val[min_counter];

		// vote- clear
		buckets[pos].val[MAX_VALID_COUNTER] = 0;

		// replace evicted flow
		buckets[pos].key[min_counter] = fp;
		buckets[pos].val[min_counter] = 0x80000001; // highest bit sets 1 -> flag was True -> query should // ? why not add f?

		return 1;
	}

/* query */
	uint32_t query(uint8_t *key)
	{
		uint32_t fp;
		int pos = CalculateFP(key, fp);

		for(int i = 0; i < MAX_VALID_COUNTER; ++i)
			if(buckets[pos].key[i] == fp)
				return buckets[pos].val[i];

		return 0;
	}


/* interface */
	// int get_memory_usage()
	// {
	// 	return bucket_num * sizeof(Bucket);
	// }
	// int get_bucket_num()
	// {
	// 	return bucket_num;
	// }

private:
	int CalculateFP(uint8_t *key, uint32_t &fp)
	{
		fp = *((uint32_t*)key); // fingerprint
		return CalculateBucketPos(fp) % bucket_num; // 得和 light part 使用不同的 hash
	}
};

#endif