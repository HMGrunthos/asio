//
// detail/freertos_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_FREETOS_TSS_PTR_HPP
#define ASIO_DETAIL_FREETOS_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_FREERTOS)

#include "asio/detail/throw_error.hpp"
#include "asio/error.hpp"

#include "asio/detail/noncopyable.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

class freertos_TSSKeyIndex {
  public:
    static const size_t FIRSTTLSOFFSET = ((size_t)free_rtos_std::gthr_freertos::eEvStoragePos) + 1;
  private:
    static const size_t NTLSPTRS = configNUM_THREAD_LOCAL_STORAGE_POINTERS - FIRSTTLSOFFSET;
  public:
    static bool usedIdxs[NTLSPTRS];
};

template <typename T>
class freertos_tss_ptr
  : private noncopyable, freertos_TSSKeyIndex
{
private:
  BaseType_t ptrIdx; // Index into the thread local pointer array

public:
  freertos_tss_ptr() {
    // Find a free index in our pointer list
    for(ptrIdx = FIRSTTLSOFFSET; ptrIdx < configNUM_THREAD_LOCAL_STORAGE_POINTERS; ptrIdx++) {
      if(usedIdxs[ptrIdx - FIRSTTLSOFFSET] == false) { // Check in the used list - this is numbered from 0 to configNUM_THREAD_LOCAL_STORAGE_POINTERS-2
        usedIdxs[ptrIdx - FIRSTTLSOFFSET] = true;
        return;
      }
    }
    // Throw an error if there are no free indicies
    asio::error_code ec(0xDEADBEEF, asio::error::get_system_category());
    asio::detail::throw_error(ec, "tss");
  }

  // Destructor.
  ~freertos_tss_ptr() {
    *this = NULL;
  }

  // Get the value.
  operator T*() const {
    // The actual TLS pointers used by this class run from 1 to configNUM_THREAD_LOCAL_STORAGE_POINTERS-1
    return (T*)pvTaskGetThreadLocalStoragePointer(NULL, ptrIdx);
  }

  // Set the value.
  void operator=(T* value) {
    vTaskSetThreadLocalStoragePointer(NULL, ptrIdx, (void*)value);
  }
};

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#if defined(ASIO_HEADER_ONLY)
# include "asio/detail/impl/freertos_tss_ptr.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // !defined(ASIO_FREERTOS)

#endif // ASIO_DETAIL_FREETOS_TSS_PTR_HPP
