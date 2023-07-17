!============================================================================
! DIRS.H                                                     Release 1.980729
!----------------------------------------------------------------------------
! This library provides an easy way of adding a 'dirs' or 'exits' verb to
! your game. Just include it somewhere after parser and verblib.
!
! >EXITS
! You can go north, south or in.
!
! In the dark, you will only know about exits in a dark room when you have
! been in that room before. You'll just have to try otherwise.
! Define Constant ShowRooms; somewhere before the inclusion of the library
! to get a display like:
!
! >EXITS
! You can go north (to the Kitchen), south (to the Living Room) or in (to the
! Closet).
!
! Bugs, comments and feedback to:
! Gunther Schmidl <sothoth@usa.net>
!
!============================================================================

System_file;

[ DirTo dir room j;
 j = dir.door_dir;
 return room.j;
];

[ DirsSub i j loc;
 if (location == thedark)
 {
  if (real_location has visited) loc = real_location;
  else "Тебе не видно ни одного выхода, потому что здесь совершенно темно.";
 }
 else loc = location;
 j = 0;
 objectloop(i in Compass)
  if(loc provides (i.door_dir) && metaclass(loc.(i.door_dir))~=nothing)
   j++;
 if (j == 0) "Нет ни одного очевидного выхода.";
 print "Ты можешь пойти ";
 objectloop(i in Compass)
 {
  if(loc provides (i.door_dir) && metaclass(loc.(i.door_dir))~=nothing)
  {
   LanguageDirection(i.door_dir);
   #ifdef ShowRooms;
    print " (", (the) DirTo(i, loc), ")";
   #endif;
   j--;
   if (j == 1) print " или ";
   else if (j == 0) ".";
   else print ", ";
  }
 }
];

Verb meta 'список'
     * 'выходов'		-> Dirs;
Verb meta 'выходы'
      *          		-> Dirs;
