#ifndef _ELASTIC_SKETCH_MY_H_
#define _ELASTIC_SKETCH_MY_H_

#include "HeavyPart.h"
#include "LightPart.h"


template<int bucket_num, int tot_memory_in_bytes>
class ElasticSketch
{
    static constexpr int heavy_mem = bucket_num * COUNTER_PER_BUCKET * 8;
    static constexpr int light_mem = tot_memory_in_bytes - heavy_mem;

    HeavyPart<bucket_num> heavy_part;
    LightPart<light_mem> light_part;

public:
    ElasticSketch(){}
    ~ElasticSketch(){}
    void clear()
    {
        heavy_part.clear();
        light_part.clear();
    }

    void insert(uint8_t *key, int f = 1)
    {
        uint8_t swap_key[KEY_LENGTH_4];
        uint32_t swap_val = 0;
        int result = heavy_part.insert(key, swap_key, swap_val, f);

        switch(result)
        {
            case 0: return;
            case 1:{
                if(HIGHEST_BIT_IS_1(swap_val))
                    light_part.insert(swap_key, GetCounterVal(swap_val));
                else
                    light_part.swap_insert(swap_key, swap_val);
                return;
            }
            case 2: light_part.insert(key, 1);  return;
            default:
                printf("error return value !\n");
                exit(1);
        }
    }

    int query(uint8_t *key)
    {
        uint32_t heavy_result = heavy_part.query(key);
        if(heavy_result == 0 || HIGHEST_BIT_IS_1(heavy_result))
        {
            int light_result = light_part.query(key);
            return (int)GetCounterVal(heavy_result) + light_result;
        }
        return heavy_result;
    }


/* interface */

    void *operator new(size_t sz)
    {
        constexpr uint32_t alignment = 64;
        size_t alloc_size = (2 * alignment + sz) / alignment * alignment;
        void *ptr = ::operator new(alloc_size);
        void *old_ptr = ptr;
        void *new_ptr = ((char*)std::align(alignment, sz, ptr, alloc_size) + alignment);
        ((void **)new_ptr)[-1] = old_ptr;

        return new_ptr;
    }
    void operator delete(void *p)
    {
        ::operator delete(((void**)p)[-1]);
    }
};



#endif
