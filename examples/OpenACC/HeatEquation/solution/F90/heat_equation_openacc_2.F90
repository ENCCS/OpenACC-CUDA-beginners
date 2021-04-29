!  2D heat equation
!
!  Copyright (C) 2014  CSC - IT Center for Science Ltd.
!

program heat_solve

  use ISO_FORTRAN_ENV, only : real32, real64

  implicit none

  integer, parameter       :: sp = real32

  integer, parameter       :: nx = 200  ! Width of the area
  integer, parameter       :: ny = 200  ! Height of the area

  real(kind=sp), parameter :: a = 0.5   ! Diffusion constant

  real(kind=sp), parameter :: dx = 0.01 ! Horizontal grid spacing
  real(kind=sp), parameter :: dy = 0.01 ! Vertical grid spacing

  real(kind=sp), parameter :: dx2 = dx*dx
  real(kind=sp), parameter :: dy2 = dy*dy

  real(kind=sp), parameter :: dt = dx2 * dy2 / (2.0 * a * (dx2+dy2))    ! Time step

  integer, parameter       :: nsteps =500       ! Number of time steps
  integer, parameter       :: outputEvery = 100 ! Image output interval

  integer, parameter       :: numElements = nx * ny

  integer :: i, j, n

  real(kind=sp)            :: radius2, ds2, uij

  character(len=85)        :: filename

  real(kind=sp), allocatable, dimension(:,:) :: Un, Unp1
 
  ! Allocate two sets of data for current and next timesteps
  allocate(Un(1:nx,1:ny))
  allocate(Unp1(1:nx,1:ny))
  
  ! Initializing the data with a pattern of disk of radius of 1/6 of the width
  radius2 = (nx / 6.0) * (nx / 6.0)
  do j = 1, ny
     do i = 1, nx
        ! Distance of point i, j from the origin
        ds2 = (i - nx/2) * (i - nx/2) + (j - ny/2)*(j - ny/2)
        if (ds2 < radius2) then
           Un(i,j) = 65.0
        else
           Un(i,j) = 5.0
        endif
     enddo
  enddo

  ! Fill in the data on the next step to ensure that the boundaries are identical.
  !  Unp1 = Un  
  do j = 1, ny
     do i = 1, nx
        Unp1(i,j) = Un(i,j)
     enddo
  enddo

  ! Main loop
!$ACC DATA COPYIN(Un) CREATE(Unp1)
  do n = 1, nsteps
     ! Going through the entire area

!!$ACC PARALLEL LOOP COPY(Un, Unp1)
!$ACC PARALLEL LOOP COLLAPSE(2) PRESENT(Un,Unp1)
     do j = 2, ny-1
        do i = 2, nx-1
           uij = Un(i,j)
           ! Explicit scheme
           Unp1(i,j) = uij + a * dt * ( (Un(i-1,j) - 2.0*uij + Un(i+1,j))/dx2 &
                &                     + (Un(i,j-1) - 2.0*uij + Un(i,j+1))/dy2 )
        enddo
     enddo

     ! Write the output if needed
     if (mod(n, outputEvery) == 0) then
!$ACC UPDATE HOST(Un)
        write(filename,'(A5,I5.5,A4,A)')  'heat_', n, '.png'
        call output(Un, nx, ny, filename)
     endif

     ! Copy the data for the next timestep
!$ACC PARALLEL LOOP COLLAPSE(2)
     do j = 1, ny
        do i = 1, nx
           Un(i,j) = Unp1(i,j)
        enddo
     enddo
  enddo
!$ACC END DATA

  ! Release the memory
  deallocate(Un);
  deallocate(Unp1);

contains

  ! Output routine, saves the temperature distribution as a png image
  ! Arguments:
  !   curr (type(field)): variable with the temperature data
  !   iter (integer): index of the time step
  subroutine output(cdata, nx, ny, filename)
    use, intrinsic :: ISO_C_BINDING
    implicit none

    real(kind=sp), dimension(:,:), intent(in) :: cdata
    integer, intent(in)           :: nx, ny
    
    character(len=85), intent(in) :: filename

    ! Interface for save_png C-function
    interface
       ! The C-function definition is
       !   int save_png(float *data,
       !                const int nx, const int ny,
       !                const char *fname, const char lang)
       function save_png(data, nx, ny, fname, lang) &
            & bind(C,name="save_png") result(stat)
         use, intrinsic :: ISO_C_BINDING
         implicit none
         real(kind=C_FLOAT) :: data(*)
         integer(kind=C_INT), value, intent(IN) :: nx, ny
         character(kind=C_CHAR), intent(IN) :: fname(*)
         character(kind=C_CHAR), value, intent(IN) :: lang
         integer(kind=C_INT) :: stat
       end function save_png
    end interface

    ! The actual write routine takes only the actual data
    ! (without ghost layers) so we need array for that
    integer :: stat
    stat = save_png(cdata, nx, ny, &
         & trim(filename) // C_NULL_CHAR, 'F')
  end subroutine output

end program
