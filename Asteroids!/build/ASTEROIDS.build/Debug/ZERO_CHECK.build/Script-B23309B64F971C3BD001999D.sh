#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/bsumma/Teaching/graphics/2022/starter_code/3 Transforms/Asteroids!/ build"
  make -f /Users/bsumma/Teaching/graphics/2022/starter_code/3\ Transforms/Asteroids!/\ build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/bsumma/Teaching/graphics/2022/starter_code/3 Transforms/Asteroids!/ build"
  make -f /Users/bsumma/Teaching/graphics/2022/starter_code/3\ Transforms/Asteroids!/\ build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/bsumma/Teaching/graphics/2022/starter_code/3 Transforms/Asteroids!/ build"
  make -f /Users/bsumma/Teaching/graphics/2022/starter_code/3\ Transforms/Asteroids!/\ build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/bsumma/Teaching/graphics/2022/starter_code/3 Transforms/Asteroids!/ build"
  make -f /Users/bsumma/Teaching/graphics/2022/starter_code/3\ Transforms/Asteroids!/\ build/CMakeScripts/ReRunCMake.make
fi

