Module DFile_Mod 
  Implicit None 
contains 
  Integer Function GetFileN( iFileUnit ) !//此函数应在打开文件后立即调用。调用后读取位置返回文件起始位置 
    Implicit None 
    Integer , Intent( IN ) :: iFileUnit 
    character( Len = 1 ) :: cDummy 
    integer :: ierr 
    GetFileN = 0 
    Rewind( iFileUnit ) 
    Do 
      Read( iFileUnit , * , ioStat = ierr ) cDummy 
      If( ierr /= 0 ) Exit 
      GetFileN = GetFileN + 1 
    End Do 
    Rewind( iFileUnit ) 
  End Function GetFileN  
End Module DFile_Mod 

program ex0716
  use DFile_Mod
  implicit none
  double precision,parameter::kB=1.38E-23,h=6.63E-34,c=2.99792458E10
  real,parameter::Tvertexcit=0,Trot=15000.0,Tvib=15000.0,Telectron=15000.0
  real,allocatable::a(:,:),b(:,:)
  integer::i=0,j=0,k=0,vv=0,nRow,students
  double precision::vibq=0,Jsum=0,xsum=0,Vsum=0,Qelectron=0,gN=1

  Open( 12 , File = 'in1rovib.txt' )
  Open(13,File = 'out.txt')
  Open(14,File = 'Qout.txt')
  nRow = GetFileN( 12 )
!  write(*,*)nRow
  students=nRow
  write(*, *) students
!  write(*,*)"how many students:"
!  read(*,*)students
  allocate(a(students,3),b(students,3))
  do i=1,students
!   write(*,"('Number ',I3)")i
   read(12,*)a(i,1),a(i,2),a(i,3)
   b(i,1)=a(i,1)
   b(i,2)=a(i,2)
   b(i,3)=a(i,3)
!  print *, i
!  write(*,*)a(i,1),a(i,2),a(i,3)
  end do
close(12)
!do i=1,nRow

!write(*,*)i, a(i,1),a(i,2),a(i,3)

!end do

  Qelectron=Exp(-h*c*Tvertexcit/(kB*Telectron))
!do i=1,nRow

!write(*,*)i, a(i,1),a(i,2),a(i,3)

!end do

do i=1,nRow
!   Print *, "i=,vibq= a(i,3)=", i,vibq,a(i,3) 
  IF ( floor(a(i,1)) <= vv)  THEN 
     j=j+1
!     Print *,"jb=",j
     ELSE
     do k=0,j-1,1
!        PRINT *, "i=, j= ,k=,i-j+k, a(1),a(2), a(3),expTrot=,i-j=, a(i-j,1),a(i-j,2),a(i-j,3)",i, j,k,i-j+k,a(i-j+k,1), a(i-j+k,2),a(i-j+k,3),Exp(-h*c*a(i-j+k,3)/(kB*Trot)),i-j,a(i-j,1),&
!         & a(i-j,2),a(i-j,3)
!        Print *, "h=, c=, a(i-j,3), kB=, Tvib= exp(xx) ",h, c, a(i-j,3),kB,Tvib,exp(-h*c*a(i-j,3)/(kB*Tvib))
        vibq=Exp(-h*c*a(i-j,3)/(kB*Tvib))
!        Print *, " vibq= ", vibq
!        Print *,"i,j,k,i-j+k-1=, a(i-j+k-1,1)=,a(i-j+k-1,2)=,a(i-j+k-1,3)= ",i,j,k,i-j+k-1, a(i-j+k-1,1),a(i-j+k-1,2),a(i-j+k-1,3)
        Print *,"i,j,k,i-j+k=, a(i-j+k,1)=,a(i-j+k,2)=,a(i-j+k,3)= ",i,j,k,i-j+k,a(i-j+k,1),a(i-j+k,2),a(i-j+k,3)

        Jsum=Jsum+gN*(2*k+1)*Qelectron*vibq*Exp(-h*c*a(i-j+k,3)/(kB*Trot))       
        b(i-j+k,3)=gN*(2*k+1)*Qelectron*vibq*Exp(-h*c*a(i-j+k,3)/(kB*Trot))
        xsum=xsum+b(i-j+k,3)
        Print *,"i,j,k,i-j+k,b(i-j+k,3),Jsum= ",i,j,k,i-j+k,b(i-j+k,3),xsum,Jsum
!        Print *, "k= Qelc=, vibq=,qrot=,b=", k,Qelectron,vibq,Exp(-h*c*a(i-j+k,3)/(kB*Trot)),b(i-j+k,3)
      end do

     PRINT *,"ja=",j
     write(*,*)i,a(i-1,1),a(i,1)
     vv=a(i,1)
     j=1
    END if

!   write(*,*)i,vibq
!   write(*,*)a(i,1),a(i,2),a(i,3)
!   write(*,*)floor(a(i,1)), floor(a(i,2)),a(i,3)
!   vv=floor(a(i,1))
!   PRINT *,a(i,1) 
!   write(*,*)i,a(i,1),a(i,2),a(i,3)
!   do while ( floor(a(i,1)) <= vv)  
!     write(*,*)"vv=",vv
!!          write(*,*)a(i,1),a(i,2),a(i,3)
!        Jsum=Jsum+gN*(2*a(i,2)+1)*Qelectron*vibq*Exp(-h*c*a(i,3)/(kB*Trot))        
!        b(i,3)=gN*(2*a(i,2)+1)*Qelectron*vibq*Exp(-h*c*a(i,3)/(kB*Trot))
!        vv=floor(a(i,1))
!       write(*,*)i,a(i,1),a(i,2),a(i,3)
        
!     END DO
  end do
  
  
!  Close(12)
  do i = 1,students
  write(13,"(1X,I5.3,5X,I5.3,5X,F15.5)")  floor(a(i,1)), floor(a(i,2)),a(i,3)
  write(13,*)  floor(a(i,1)), floor(a(i,2)),a(i,3)
  end do

  Close(13)
Print *,"Sum=",Jsum
  xsum=0
  do i = 1,students-1
!  write(14,"(1X,I5.3,5X,I5.3,5X,F15.5)")  floor(a(i,1)), floor(a(i,2)),a(i,3)
  write(14,*)  floor(b(i,1)), floor(b(i,2)),b(i,3)
  xsum=xsum+b(i,3)
! Print *, "i,b(i,3), xsum=",i,b(i,3), xsum
  end do
  Close(14)
PRINT * , "xsum= ", xsum
 stop
end
