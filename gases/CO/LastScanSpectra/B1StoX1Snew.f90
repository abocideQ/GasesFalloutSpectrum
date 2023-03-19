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
  double precision,parameter::cspeed=2.99792458E10
  real,parameter::Tvertexcit=86945.2,Tground=0.0
  real,allocatable::a(:,:),b(:,:),c(:,:)
  integer::i,iu=1,iuc=0,ju=1,il=1,jl=0,juu=1,vv=0,ww=0,n1Row,n2Row,students
  double precision::vibq=0,Jsum=0,xsum=0,Vsum=0,Qelectron=0,gN=1

  Open( 12 , File = '1.txt' )
  Open(13,File = '4.txt')
  Open(14,File = '3.txt')
  n1Row = GetFileN( 12 )
  n2Row = GetFileN(13)
!  write(*,*)nRow
  students=n1Row
  write(*, *) students
!  write(*,*)"how many students:"
!  read(*,*)students
  allocate(a(n1Row,3),b(n2Row,3),c(n1Row,3))
  do i=1,n1Row
!   write(*,"('Number ',I3)")i
   read(12,*)a(i,1),a(i,2),a(i,3)
   c(i,1)=a(i,1)
   c(i,2)=a(i,2)
   c(i,3)=a(i,3)
!  print *, i
!  write(*,*)a(i,1),a(i,2),a(i,3)
  end do
close(12)
  do i=1,n2Row
   read(13,*)b(i,1),b(i,2),b(i,3)
  end do
close(13)
!do i=1,n1Row
!write(*,*)i, a(i,1),a(i,2),a(i,3)
!end do
do il=1,n1Row
!   Print *, "i=,vibq= a(i,3)=", il,a(il,3) 
  IF ( floor(a(il,1)) <= vv)  THEN
     jl=jl+1
    ELSE
     do while (iu <= n2Row)
        IF ( floor(b(iu,1)) <= ww)  THEN
           ju=ju+1
           ELSE
            do  juu=1, ju-1
!              write(*,*)iu,juu,b(iu-ju+juu,1),b(iu-ju+juu,2),b(iu-ju+juu,3)
               print *,a(il-1-jl+juu,1),a(il-1-jl+juu,2),a(il-1-jl+juu,3)
                 IF (a(il-1-jl+juu+1,1)> b(iu-ju+juu,1)) THEN 
                    ju=1
                    exit 
                   END if
                 write(14,"(6I6,1X,2F14.4)")floor(b(iu-ju+juu,1)),floor(a(il-1-jl+juu+1,1)),floor(b(iu-ju+juu,1)-a(il-1-jl+juu+1,1)),floor(b(iu-ju+juu,2)), &
                        &  floor(a(il-1-jl+juu+1,2)),floor(b(iu-ju+juu,2)-a(il-1-jl+juu+1,2)),Tvertexcit+b(iu-ju+juu,3)-Tground-a(il-1-jl+juu+1,3), &
                        &   1E8/(Tvertexcit+b(iu-ju+juu,3)-Tground-a(il-1-jl+juu+1,3))
                 write(14,"(6I6,1X,2F14.4)")floor(b(iu-ju+juu,1)),floor(a(il-1-jl+juu,1)),floor(b(iu-ju+juu,1)-a(il-1-jl+juu,1)),floor(b(iu-ju+juu,2)), &
                        & floor(a(il-1-jl+juu,2)),floor(b(iu-ju+juu,2)-a(il-1-jl+juu,2)),Tvertexcit+b(iu-ju+juu,3)-Tground-a(il-1-jl+juu,3),1E8/(Tvertexcit+b(iu-ju+juu,3)-Tground-a(il-1-jl+juu,3))
               if (juu < ju-1) then
!                 write(14,"(6I5,4X,F11.4)")floor(b(iu-ju+juu+1,1)),floor(a(il-1-jl+juu,1)),floor(a(il-1-jl+juu,1)-a(il-1-jl+juu,1)),juu+1,juu,juu+1-juu,Tvertexcit+b(iu-ju+juu+1,3)-a(il-1-jl+juu,3)
                 write(14,"(6I6,1X,2F14.4)")floor(b(iu-ju+juu+1,1)),floor(a(il-1-jl+juu,1)),floor(a(il-1-jl+juu,1)-a(il-1-jl+juu,1)), &
                        & floor(b(iu-ju+juu+1,2)), floor(a(il-1-jl+juu,2)), floor(b(iu-ju+juu+1,2)-a(il-1-jl+juu,2)),Tvertexcit+b(iu-ju+juu+1,3)-Tground-a(il-1-jl+juu,3),&
                        & 1E8/(Tvertexcit+b(iu-ju+juu+1,3)-Tground-a(il-1-jl+juu,3))
                 end if
            end do
             ww=b(iu,1)
             ju=1
          exit
         end if
         iu = iu + 1
       end do
     vv=a(il,1)
     jl=1
    end if
end do 
close(14)
 stop
end
