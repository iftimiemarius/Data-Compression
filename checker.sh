make clean
make

printf "TESTING LZW COMPRESSION:\n"

for (( i=0; i < 10; i++ )); do
  printf "| Test $i "
	./tester in/test$i.in out/test$i.out out_decompressed/test$i.out lzw
	diff in/test$i.in out_decompressed/test$i.out
	if [ $? -ne 0 ]; then
		printf "FAILED"
	else
		printf "PASSED"
	fi
	printf " |\n"
done

rm -rf out/* out_decompressed/*

printf "TESTING HUFFMAN CODING:\n"

for (( i=0; i < 10; i++ )); do
	printf "| Test $i "
	./tester in/test$i.in out/test$i.out out_decompressed/test$i.out huffman
	diff in/test$i.in out_decompressed/test$i.out
	if [ $? -ne 0 ]; then
		printf "FAILED"
	else
		printf "PASSED"
	fi
	printf " |\n"
done

#make clean
