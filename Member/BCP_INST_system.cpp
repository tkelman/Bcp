// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.

#include <vector>
template class std::vector<double*>;

//-----------------------------------------------------------------------------

#include <algorithm>
#include <numeric>
#include <functional>

#include "BCP_os.hpp"

template int const *
std::find_if(int const *, int const *, binder2nd< std::greater_equal<int> >);
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template char *
std::find_if(char *, char *, int (*)(int), random_access_iterator_tag);
#endif

template int *
std::set_union(int *, int *, int *, int *, int *);

template int *
std::rotate(int *, int *, int *);
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template int *
__rotate(int *, int *, int *, BCP_PtrDiff *, bidirectional_iterator_tag);
#endif

//-----------------------------------------------------------------------------
// template <class RandomAccessIterator, class Compare>
// inline void sort(RandomAccessIterator first, RandomAccessIterator last,
//                  Compare comp);
//-----------------------------------------------------------------------------
class BCP_lp_waiting_row;
template void std::sort(BCP_lp_waiting_row **, BCP_lp_waiting_row **,
			bool(*)(BCP_lp_waiting_row const *,
				BCP_lp_waiting_row const *));
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template void
__final_insertion_sort(BCP_lp_waiting_row **, BCP_lp_waiting_row **,
		       int(*)(BCP_lp_waiting_row const *,
			      BCP_lp_waiting_row const *));
template void
__introsort_loop(BCP_lp_waiting_row **, BCP_lp_waiting_row **,
		 BCP_lp_waiting_row **, BCP_PtrDiff,
		 int(*)(BCP_lp_waiting_row const *,
			BCP_lp_waiting_row const *));
#endif
//-----------------------------------------------------------------------------
class BCP_lp_waiting_col;
template void std::sort(BCP_lp_waiting_col **, BCP_lp_waiting_col **,
			bool(*)(BCP_lp_waiting_col const *,
				BCP_lp_waiting_col const *));
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template void
__final_insertion_sort(BCP_lp_waiting_col **, BCP_lp_waiting_col **,
		       int(*)(BCP_lp_waiting_col const *,
			      BCP_lp_waiting_col const *));
template void
__introsort_loop(BCP_lp_waiting_col **, BCP_lp_waiting_col **,
		 BCP_lp_waiting_col **, BCP_PtrDiff,
		 int(*)(BCP_lp_waiting_col const *,
			BCP_lp_waiting_col const *));
#endif
//-----------------------------------------------------------------------------
class BCP_var_indexed;
template void std::sort(BCP_var_indexed const **, BCP_var_indexed const **,
			bool(*)(BCP_var_indexed const *,
				BCP_var_indexed const *));
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template void
__final_insertion_sort(BCP_var_indexed const **, BCP_var_indexed const **,
		       int(*)(BCP_var_indexed const *,
			      BCP_var_indexed const *));
template void
__introsort_loop(BCP_var_indexed const **, BCP_var_indexed const **,
		 BCP_var_indexed const **, BCP_PtrDiff,
		 int(*)(BCP_var_indexed const *, BCP_var_indexed const *));
#endif
//-----------------------------------------------------------------------------
template void std::sort(std::pair<int,int>*, std::pair<int,int>*,
			bool(*)(const std::pair<int,int>&, 
				const std::pair<int,int>&));
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template void
__final_insertion_sort(std::pair<int,int>*, std::pair<int,int>*,
		       int(*)(const std::pair<int,int>&, 
			      const std::pair<int,int>&));
template void
__introsort_loop(std::pair<int,int>*, std::pair<int,int>*, 
		 std::pair<int,int>*, BCP_PtrDiff,
		 int(*)(const std::pair<int,int>&, const std::pair<int,int>&));

#endif
//-----------------------------------------------------------------------------

template void std::sort(int *, int *);
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template void __final_insertion_sort(int *, int *);
template void __introsort_loop(int *, int *, int *, BCP_PtrDiff);
#endif

//-----------------------------------------------------------------------------
template void std::sort(double *, double *);
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template void __final_insertion_sort(double *, double *);
template void __introsort_loop(double *, double *, double *, BCP_PtrDiff);
#endif

//-----------------------------------------------------------------------------
// template <class ForwardIterator, class T, class Distance>
// ForwardIterator __upper_bound(ForwardIterator first,
// 			      ForwardIterator last,
//                               const T& value, Distance*,
//                               forward_iterator_tag);
template double *
std::lower_bound(double *, double *, double const &);
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template double *
__lower_bound(double *, double *, double const &, BCP_PtrDiff *);
#endif

template double *
std::upper_bound(double *, double *, double const &);
#ifdef NEED_IMPLICIT_TEMPLATE_FUNCTIONS
template double *
__upper_bound(double *, double *, double const &, BCP_PtrDiff  *);
#endif


template int *
std::max_element(int *, int *);

// template <class InputIterator, class OutputIterator, class UnaryFunction>
// OutputIterator transform(InputIterator first, InputIterator last,
//                          OutputIterator result, UnaryFunction op);
template int *
std::transform(int *, int *, int *, binder2nd<minus<int> >);

//  template <class InputIterator, class OutputIterator>
//  OutputIterator partial_sum(InputIterator first, InputIterator last,
//                             OutputIterator result);
template int *
std::partial_sum(int *, int *, int *);

template void
std::fill(double *, double *, double const &);

template void
std::fill(int *, int *, int const &);

//#############################################################################

#include <map>

class BCP_var;
class BCP_cut;

template class std::map<BCP_IndexType, BCP_var*>;
template class std::map<BCP_IndexType, BCP_cut*>;

#ifdef NEED_IMPLICIT_TEMPLATE_CLASSES
template class std::_Rb_tree
< int,
  std::pair<int const, BCP_var *>,
  std::_Select1st<std::pair<int const, BCP_var *> >,
  std::less<int>,
  std::allocator<BCP_var *>
>;
template class std::_Rb_tree
<  int,
  std::pair<int const, BCP_cut *>,
  std::_Select1st<std::pair<int const, BCP_cut *> >,
  std::less<int>,
  std::allocator<BCP_cut *>
>;
#endif

