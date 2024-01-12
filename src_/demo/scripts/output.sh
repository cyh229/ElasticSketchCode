#!/bin/bash
# 在 src/CPU/demo 下执行，输出到 src/CPU/demo/output

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

  # 输出执行信息，可选
  echo "Executed $file, output redirected to $output_path"
done
