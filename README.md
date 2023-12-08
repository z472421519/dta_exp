## Enviroment configure
> Ubuntu 20.04
```bash
bash clang-llvm-install.sh
ln -sf /usr/bin/clang-11 /usr/bin/clang
```
## Build dta_exp
```bash
cd dta_exp
mkdir build
cd build
cmake .. -DDTAINT_DEBUG=ON
```