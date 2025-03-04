// Support routines for the -*- C++ -*- dynamic memory management.

// Copyright (C) 1997-2016 Free Software Foundation, Inc.
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// GCC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include <bits/c++config.h>
#include <stdlib.h>
#include <bits/exception_defines.h>
#include "new"

using std::new_handler;
using std::bad_alloc;

#if !_GLIBCXX_HAVE_ALIGNED_ALLOC
#if _GLIBCXX_HAVE__ALIGNED_MALLOC
#define aligned_alloc(al,sz) _aligned_malloc(sz,al)
#elif _GLIBCXX_HAVE_POSIX_MEMALIGN
static inline void*
aligned_alloc (std::size_t al, std::size_t sz)
{
  void *ptr;
  int ret = posix_memalign (&ptr, al, sz);
  if (ret == 0)
    return ptr;
  return nullptr;
}
#elif _GLIBCXX_HAVE_MEMALIGN
#include <malloc.h>
#define aligned_alloc memalign
#else
// The C library doesn't provide any aligned allocation functions, declare
// aligned_alloc and get a link failure if aligned new is used.
extern "C" void *aligned_alloc(std::size_t, std::size_t);
#endif
#endif

_GLIBCXX_WEAK_DEFINITION void *
operator new (std::size_t sz, std::align_val_t al)
{
  void *p;

  /* malloc (0) is unpredictable; avoid it.  */
  if (sz == 0)
    sz = 1;

  while (__builtin_expect ((p = aligned_alloc ((std::size_t)al, sz)) == 0,
			   false))
    {
      new_handler handler = std::get_new_handler ();
      if (! handler)
	_GLIBCXX_THROW_OR_ABORT(bad_alloc());
      handler ();
    }

  return p;
}
