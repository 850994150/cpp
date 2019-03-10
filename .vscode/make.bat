set cpp_path=%1
set "cpp_path=%cpp_path:\=/%"
bash -c "rm -f %2 && g++ --std=c++11 -g %cpp_path% -o %2 -lpthread && clear && time %2"