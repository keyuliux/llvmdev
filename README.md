
install from prebuild binary

cp llvm prebuild to /usr/local/

sudo gedit /etc/profile
export LLVM_HOME=/usr/local/llvm/bin
export PATH=$LLVM_HOME:$PATH

Fix llvm3.8 cmake error
sudo apt-get install -y llvm-3.8-dev libclang-3.8-dev
sudo mkdir -p /usr/lib/llvm-3.8/share/llvm
sudo ln -s /usr/share/llvm-3.8/cmake /usr/lib/llvm-3.8/share/llvm/cmake
sudo sed -i -e '/get_filename_component(LLVM_INSTALL_PREFIX/ {s|^|#|}' -e '/^# Compute the installation prefix/i set(LLVM_INSTALL_PREFIX "/usr/lib/llvm-3.8")' /usr/lib/llvm-3.8/share/llvm/cmake/LLVMConfig.cmake
sudo sed -i '/_IMPORT_CHECK_TARGETS Polly/ {s|^|#|}' /usr/lib/llvm-3.8/share/llvm/cmake/LLVMExports-relwithdebinfo.cmake
sudo sed -i '/_IMPORT_CHECK_TARGETS sancov/ {s|^|#|}' /usr/lib/llvm-3.8/share/llvm/cmake/LLVMExports-relwithdebinfo.cmake
sudo ln -s /usr/lib/x86_64-linux-gnu/libLLVM-3.8.so.1 /usr/lib/llvm-3.8/lib/

install antlr
 1850  wget http://www.antlr.org/download/antlr-4.6-complete.jar
sudo gedit /etc/profile
export CLASSPATH=".:/path/to/antlr-4.6-complete.jar:$CLASSPATH"
sudo gedit ~/.bashrc
alias antlr4='java -jar /path/to/antlr-4.6-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'

antlr4 -Dlanguage=Cpp -no-listener -visitor LabeledExpr.g4 
grun Expr prog -gui t.expr

frontend-antlr4
antlr4 Hello.g4 -visitor
antlr4 -Dlanguage=Cpp Lua.g4 -visitor

backend-llvm

Chapter3

$clang hello.c -o hello

$clang -### hello.c -o hello

$clang main.c sum.c -o sum

$clang -emit-llvm -c main.c -o main.bc

$clang -emit-llvm -c sum.c -o sum.bc

$clang -emit-llvm -S main.c -o main.ll

$clang -emit-llvm -S sum.c -o sum.ll

$llc -filetype=obj main.bc -o main.o
$llc -filetype=obj sum.bc -o sum.o
$clang main.o sum.o -o sum

$llvm-link main.bc sum.bc -o sum.linked.bc
$llc -filetype=obj sum.linked.bc -o sum.linked.o
$clang sum.linked.o -o sum


Chapter4

Libraries
libclangLex
libclangAST
libclangParse
libclangSema
libclangCodeGen
libclangAnalysis
libclangRewrite
libclangBasic

$clang -Xclang -ast-dump hello.c
$clang -cc1 -ast-dump hello.c

$clang hello.c -###

$clang -cc1 -dump-tokens min.c


$clang -E pp.c -o pp2.c

$pp-trace pp.c

$clang -fsyntax-only -Xclang -ast-dump min.c
$clang -fsyntax-only -Xclang -ast-view min.c

$gdb clang
(gdb) b ParseStmt.cpp:213
(gdb) r -cc1 -fsyntax-only min.c
(gdb) backtrace

$clang -x c-header myheader.h -o myheader.h.pch
$clang -include myheader.h myproject.c -o myproject

$clang -fsyntax-only -Xclang -print-decl-contexts min.c

$gdb clang
(gdb) b CGStmt.cpp:130
(gdb) r -cc1 -emit-obj min.c

Chapter5

$clang sum.c -emit-llvm -c -o sum.bc
$clang sum.c -emit-llvm -S -c -o sum.ll
$llvm-as sum.ll -o sum.bc
$llvm-dis sum.bc -o sum.ll

$llvm-extract -func=sum sum.bc -o sum-fun.bc

// Learning how to write code to generate any IR construct with the C++ backend
$llc -march=cpp sum.bc -o sum.cpp

$opt -O3 sum.bc -o sum-O3.bc
$opt -std-compile-opts sum.bc -o sum-stdc.bc

$llvm-link file1.bc file2.bc file3.bc -o=all.bc
$opt -std-link-opts all.bc -o all-stdl.bc

$opt sum.bc -mem2reg -instcount -o sum-tmp.bc -stats

$opt sum.bc -time-passes -domtree -instcount -o sum-tmp.bc

$opt -O1 sum-O0.ll -S -o sum-O1.ll

$clang -Xclang -print-stats -emit-llvm -O1 sum.c -c -o sum-O1.bc
$opt sum-O0.ll -stats -sroa -o sum-O1.ll
$opt sum-O0.11 -stats -mem2reg -o sum-O1.ll

$opt sum-O0.ll -debug-pass=Structure -mem2reg -S -o sum-O1.ll

Chapter6

$llc sum.bc -o sum.s
$llc sum.bc -filetype=obj -o -sum.o
$llc -march=mips -filetype=obj sum.bc -o sum.o

main directory
CodeGen
MC
TableGen
Target

$llvm-tblgen -print-records insns.td

$llc -march=sparc -print-machineinstrs sum.bc

$llc -march=sparc -debug-only=regalloc sum.bc

$clang -emit-llvm -c sum-main.c -o sum-main.bc
$lli sum-main.bc

$lli -use-mcjit sum-main.bc
$lli -force-interpreter sum-main.bc

Clang
CodeGenFunction Class Emit*** function

from 2.3 release, we could see each patch in reviews web.
https://reviews.llvm.org/source/llvm-github/history/release%252F2.3.x/clang/lib/CodeGen/

llvm bindings
llvm_ocaml.c

llvm2.1
LLVMBuilder.h





