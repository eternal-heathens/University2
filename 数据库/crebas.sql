/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2012                    */
/* Created on:     2019/11/23 18:51:17                          */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('elective') and o.name = 'FK_ELECTIVE_ELECTIVE_COURSE31')
alter table elective
   drop constraint FK_ELECTIVE_ELECTIVE_COURSE31
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('elective') and o.name = 'FK_ELECTIVE_ELECTIVE2_STUDENT3')
alter table elective
   drop constraint FK_ELECTIVE_ELECTIVE2_STUDENT3
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('student3117004816֣�ķ�') and o.name = 'FK_STUDENT3_STUDENT_M_MANAGER3')
alter table student3117004816֣�ķ�
   drop constraint FK_STUDENT3_STUDENT_M_MANAGER3
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('teacher3117004816֣�ķ�') and o.name = 'FK_TEACHER3_TEACHER_M_MANAGER3')
alter table teacher3117004816֣�ķ�
   drop constraint FK_TEACHER3_TEACHER_M_MANAGER3
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('teaching') and o.name = 'FK_TEACHING_TEACHING_TEACHER3')
alter table teaching
   drop constraint FK_TEACHING_TEACHING_TEACHER3
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('teaching') and o.name = 'FK_TEACHING_TEACHING2_COURSE31')
alter table teaching
   drop constraint FK_TEACHING_TEACHING2_COURSE31
go

if exists (select 1
            from  sysobjects
           where  id = object_id('course3117004816֣�ķ�')
            and   type = 'U')
   drop table course3117004816֣�ķ�
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('elective')
            and   name  = 'elective2_FK'
            and   indid > 0
            and   indid < 255)
   drop index elective.elective2_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('elective')
            and   type = 'U')
   drop table elective
go

if exists (select 1
            from  sysobjects
           where  id = object_id('manager3117004816֣�ķ�')
            and   type = 'U')
   drop table manager3117004816֣�ķ�
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('student3117004816֣�ķ�')
            and   name  = 'student_manage_FK'
            and   indid > 0
            and   indid < 255)
   drop index student3117004816֣�ķ�.student_manage_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('student3117004816֣�ķ�')
            and   type = 'U')
   drop table student3117004816֣�ķ�
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('teacher3117004816֣�ķ�')
            and   name  = 'teacher_manage_FK'
            and   indid > 0
            and   indid < 255)
   drop index teacher3117004816֣�ķ�.teacher_manage_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('teacher3117004816֣�ķ�')
            and   type = 'U')
   drop table teacher3117004816֣�ķ�
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('teaching')
            and   name  = 'teaching2_FK'
            and   indid > 0
            and   indid < 255)
   drop index teaching.teaching2_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('teaching')
            and   type = 'U')
   drop table teaching
go

/*==============================================================*/
/* Table: course3117004816֣�ķ�                                   */
/*==============================================================*/
create table course3117004816֣�ķ� (
   cno                  char(20)             not null,
   cname                char(20)             null,
   cteacher             char(20)             null,
   ccredit              char(20)             null,
   cperiod              char(20)             null,
   constraint PK_COURSE3117004816֣�ķ� primary key (cno)
)
go

/*==============================================================*/
/* Table: elective                                              */
/*==============================================================*/
create table elective (
   sno                  char(20)             not null,
   cno                  char(20)             not null,
   grade                char(20)             null,
   constraint PK_ELECTIVE primary key (sno, cno)
)
go

/*==============================================================*/
/* Index: elective2_FK                                          */
/*==============================================================*/
create index elective2_FK on elective (
sno ASC
)
go

/*==============================================================*/
/* Table: manager3117004816֣�ķ�                                  */
/*==============================================================*/
create table manager3117004816֣�ķ� (
   mno                  char(20)             not null,
   mimpermission        char(20)             null,
   mname                char(20)             null,
   constraint PK_MANAGER3117004816֣�ķ� primary key (mno)
)
go

/*==============================================================*/
/* Table: student3117004816֣�ķ�                                  */
/*==============================================================*/
create table student3117004816֣�ķ� (
   sno                  char(20)             not null,
   mno                  char(20)             null,
   sname                char(20)             not null,
   sclass               char(20)             null,
   speciaty             char(20)             null,
   ssex                 char(20)             null,
   sbirthday            char(20)             null,
   constraint PK_STUDENT3117004816֣�ķ� primary key (sno)
)
go

/*==============================================================*/
/* Index: student_manage_FK                                     */
/*==============================================================*/
create index student_manage_FK on student3117004816֣�ķ� (
mno ASC
)
go

/*==============================================================*/
/* Table: teacher3117004816֣�ķ�                                  */
/*==============================================================*/
create table teacher3117004816֣�ķ� (
   tno                  char(20)             not null,
   mno                  char(20)             null,
   tname                char(20)             null,
   time                 char(20)             null,
   tcourse              char(20)             null,
   constraint PK_TEACHER3117004816֣�ķ� primary key (tno)
)
go

/*==============================================================*/
/* Index: teacher_manage_FK                                     */
/*==============================================================*/
create index teacher_manage_FK on teacher3117004816֣�ķ� (
mno ASC
)
go

/*==============================================================*/
/* Table: teaching                                              */
/*==============================================================*/
create table teaching (
   cno                  char(20)             not null,
   tno                  char(20)             not null,
   duration             char(20)             null,
   class                char(20)             null,
   constraint PK_TEACHING primary key (cno, tno)
)
go

/*==============================================================*/
/* Index: teaching2_FK                                          */
/*==============================================================*/
create index teaching2_FK on teaching (
cno ASC
)
go

alter table elective
   add constraint FK_ELECTIVE_ELECTIVE_COURSE31 foreign key (cno)
      references course3117004816֣�ķ� (cno)
go

alter table elective
   add constraint FK_ELECTIVE_ELECTIVE2_STUDENT3 foreign key (sno)
      references student3117004816֣�ķ� (sno)
go

alter table student3117004816֣�ķ�
   add constraint FK_STUDENT3_STUDENT_M_MANAGER3 foreign key (mno)
      references manager3117004816֣�ķ� (mno)
go

alter table teacher3117004816֣�ķ�
   add constraint FK_TEACHER3_TEACHER_M_MANAGER3 foreign key (mno)
      references manager3117004816֣�ķ� (mno)
go

alter table teaching
   add constraint FK_TEACHING_TEACHING_TEACHER3 foreign key (tno)
      references teacher3117004816֣�ķ� (tno)
go

alter table teaching
   add constraint FK_TEACHING_TEACHING2_COURSE31 foreign key (cno)
      references course3117004816֣�ķ� (cno)
go

