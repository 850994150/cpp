
# .PHONY : file.so CLoadSo

# 生成 firstso
first.so : filea.c fileb.c
	g++ -Wall -fpic -g -shared filea.c fileb.c -o first.so

# 生成可执行文件CLoadSo
CLoadSo : CLoadSo.c
	gcc -g -Wall CLoadSo.c -o CLoadSo -ldl


