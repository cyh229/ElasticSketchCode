#!/bin/bash

# 新的DFLAGs值
START_FILE_NO=1
END_FILE_NO=10
TOT_MEM_IN_BYTES=$((600 * 1024))

# Makefile路径变量
cd ..
MAKEFILE_PATH="Makefile"

# 保存原始DFLAGs值
ORIGINAL_DFLAGS=$(sed -n '/^DFLAGs =/p' $MAKEFILE_PATH)

result_path="scripts/exp.csv"
# if [ ! -e "$file_path" ]; then # 检查不存在
echo "sketch,memory(KB),idx,ARE" > $result_path # 字段

for ((i = 200; i <= 1000; i += 100)); do
    TOT_MEM_IN_BYTES=$((i * 1024))
    # 修改Makefile中的DFLAGs
    NEW_DFLAGS="-DSTART_FILE_NO=$START_FILE_NO -DEND_FILE_NO=$END_FILE_NO -DTOT_MEM_IN_BYTES=$TOT_MEM_IN_BYTES"
    sed -i "s/DFLAGs =.*/DFLAGs = $NEW_DFLAGS/" $MAKEFILE_PATH

    # 查看修改情况
    # cat $MAKEFILE_PATH

    make clean
    # 执行make并记录输出到log文件
    make -C $(dirname $MAKEFILE_PATH) # > log.txt 2>&1
    # cd scripts

    ############################################################
    # 数组包含所有的 .out 文件名
    files=("elastic.out" "elastic_my.out" "cmsketch.out" "cusketch.out" "countsketch.out")

    # 检查文件夹是否存在并在不存在时创建它
    if [ ! -d output ]; then
        mkdir output
    fi

    # 循环遍历数组中的每个文件名
    for file in "${files[@]}"; do
        # 构建输出文件的路径
        output_path="output/${file%.*}.output"
        
        # 执行相应的 .out 文件，并将输出到对应的路径
        # echo $output_path
        time ./"$file" > "$output_path" # 直接覆盖，计时 # 并行执行
        
        # 提取组数和结果
        while IFS= read -r line; do
            if [[ $line =~ ([0-9]+)\.dat:[[:space:]]ARE=([0-9.]+) ]]; then
                data_idx="${BASH_REMATCH[1]}"
                ARE_result="${BASH_REMATCH[2]}"
                echo "${file%.*}, $i, $data_idx, $ARE_result" >> $result_path
            fi
        done < "$output_path"
        
        # 输出执行信息，可选
        echo "Executed $file, output redirected to $output_path"
    done
done
############################################################
# 恢复原始DFLAGs值
sed -i "s/DFLAGs =.*/$ORIGINAL_DFLAGS/" $MAKEFILE_PATH
