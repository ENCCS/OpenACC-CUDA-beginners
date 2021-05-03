program vectorsum
#ifdef _OPENACC
  use openacc
#endif
  implicit none
  integer, parameter :: rk = selected_real_kind(12)
  integer, parameter :: ik = selected_int_kind(9)
  integer, parameter :: nx = 102400

  real(kind=rk), dimension(nx) :: vecA, vecB, vecC
  real(kind=rk)    :: sum
  integer(kind=ik) :: i

  ! Initialization of vectors
  do i = 1, nx
     vecA(i) = 1.0_rk/(real(nx - i + 1, kind=rk))
     vecB(i) = vecA(i)**2
  end do

  !$acc parallel
  !$acc loop
  do i = 1, nx
     vecC(i) = add(vecA(i), vecB(i))
  end do
  !$acc end loop
  !$acc end parallel loop

  ! Compute the check value
  write(*,*) 'Reduction sum: ', sum(vecC)

contains

  real(kind=rk) function add(a, b)
!$acc routine seq
    implicit none
    real(kind=rk), intent(in) :: a, b
    
    add = a + b
    return 
  end function add
  
end program vectorsum
