///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2010 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#define FIXED_POINT_DISABLE_IOSTREAM

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>
#include <math/calculus/derivative.h>
#include <math/fixed_point/fixed_point.h>

namespace
{
  using fixed_point_type = fixed_point<std::int32_t>;
}

extern fixed_point_type global_a;
extern fixed_point_type global_b;
extern fixed_point_type global_c;
extern fixed_point_type global_d;

bool app::benchmark::run_fixed_point()
{
  const fixed_point_type a = global_a;
  const fixed_point_type b = global_b;
  const fixed_point_type c = global_c;

  global_d = math::derivative(fixed_point_type(1) / 2,  // x
                              fixed_point_type(1) / 4,  // Step size dx.
                              [&a, &b, &c](const fixed_point_type& x) -> fixed_point_type
                              {
                                return (((a * x) + b) * x) + c;
                              });

  const fixed_point_type control   = fixed_point_type(46U) /   10U;
  const fixed_point_type tolerance = fixed_point_type( 1U) / 1000U;

  const bool result_is_ok = detail::is_close_fraction(global_d,
                                                      control,
                                                      tolerance);

  return result_is_ok;
}

fixed_point_type global_a = fixed_point_type(12) / 10;
fixed_point_type global_b = fixed_point_type(34) / 10;
fixed_point_type global_c = fixed_point_type(56) / 10;
fixed_point_type global_d;
