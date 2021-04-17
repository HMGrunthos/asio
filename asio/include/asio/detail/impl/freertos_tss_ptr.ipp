//
// detail/impl/freertos_tss_ptr.ipp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_IMPL_FREERTOS_TSS_PTR_IPP
#define ASIO_DETAIL_IMPL_FREERTOS_TSS_PTR_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_FREERTOS)

#include "asio/detail/freertos_tss_ptr.hpp"
#include "asio/detail/throw_error.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
  namespace detail {
    template <typename T> bool *freertos_tss_ptr<T>::usedPtrIdxs = NULL;
  } // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // defined(ASIO_FREERTOS)

#endif // ASIO_DETAIL_IMPL_FREERTOS_TSS_PTR_IPP
