//
// detail/null_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_FREETOS_GLOBAL_HPP
#define ASIO_DETAIL_FREETOS_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

template <typename T>
struct freertos_global_impl
{
  freertos_global_impl()
    : ptr_(0)
  {
  }

  // Destructor automatically cleans up the global.
  ~freertos_global_impl()
  {
    delete ptr_;
  }

  static freertos_global_impl instance_;
  static std::mutex mutex_;
  T* ptr_;
};

template <typename T> freertos_global_impl<T> freertos_global_impl<T>::instance_;

template <typename T> std::mutex freertos_global_impl<T>::mutex_;

template <typename T>
T& freertos_global()
{
  {
    freertos_global_impl<T>::mutex_.lock();
      if (freertos_global_impl<T>::instance_.ptr_ == 0)
        freertos_global_impl<T>::instance_.ptr_ = new T;
    freertos_global_impl<T>::mutex_.unlock();
  }
  return *freertos_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_DETAIL_FREETOS_GLOBAL_HPP
