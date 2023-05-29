#!/usr/bin/bash
###########################################################################################
#                                    e4
###########################################################################################
# there's a project.sh in root of the project. before do anything, source it: . project.sh
#
# tools:
# static code analyzer:
#   - c: splint
# memory debugger: valgrind
# system call tracer: strace
# display info about .obj files: objdump
#
# opening/editing files: noevim
#   folding/unfolding: z Shift+m, z Shift+r
#   switch between source/header: F1
#
# lookup refrences: ctags
# find/replace in single file: neovim
# find/replace in whole project: ambr <source_text> <dest_text>
# find files: ctrl-t | ff <file-name> | fzf | fd
# find string/text in single file: neovim (/)
# find string/text in whole project: ft <text> | rg <text>
# find docs of c standard librariy: install man-pages-devel and man <method>
#
# debugging: seergdb(uses gdb under the hood)
###########################################################################################
# pardis, test
app=""

# debug, release, test
mode="debug"
build_dir="build/$mode"

mode_flags=""
if [ "$mode" == "debug" ]; then
  app="e4"
  mode_flags="-g -O0"
fi

if [ "$mode" == "release" ]; then
  app="e4"
  mode_flags="-O3"
fi

if [ "$mode" == "test" ]; then
  app="e4_test"
fi

_createBuildDir() {
  echo ">>> Creating '$build_dir' directory"
  mkdir -p "$build_dir"
}

_generateTags() {
  echo ">>> generating tags"
  ctags --fields=+iaS --extras=+q --extras=+f -R *
}

_compile() {
  compiler="cc"
  flags="-lSDL2 -lSDL2_ttf -lm"
  src="lib/*.c example/*.c"

  echo ">>> Compiling ($mode)"
  $compiler $mode_flags $flags -o $build_dir/$app $src
}

_build() {
  _createBuildDir
  _generateTags
  _compile
  cp assets/monaco.ttf $build_dir
  #cp assets/FantasqueSansMono.ttf $build_dir
}

_debug() {
  cd $build_dir
  seergdb -s $app
  cd ../..
}

_run() {
  echo ">>> Running $app - $mode"
  cd $build_dir
  ./$app
  cd ../..
}

_clean() {
  echo ">>> Cleaning '$build_dir' directory"
  rm -r "$build_dir"
}

_valgrind() {
  valgrind --leak-check=yes --show-leak-kinds=all -s -v $build_dir/$app
}

_findStrings() {
  strings $build_dir/$app | less
}

_findSymbolsInObj() {
  nm $build_dir/$app | less
}

p() {
  commands=("build" "run" "clean" "debug" "generate tags" "valgrind" "find strings in the binary" "list symbols from object files")
  selected=$(printf '%s\n' "${commands[@]}" | fzf --header="project:")

  case $selected in
    "build")
      _build;;
    "debug")
      _debug;;
    "run")
      _run;;
    "clean")
      _clean;;
    "generate tags")
      _generateTags;;
    "valgrind")
      _valgrind;;
    "find strings in the binary")
      _findStrings;;
    "list symbols from object files")
      _findSymbolsInObj;;
    *) ;;
  esac
}
