先打開該資料夾裡面的 CMD 之後，輸入

> gcc split_file.c
> a DB_students.csv DB_students_tc_big5.csv
> 
> gcc cid_file_index.c
> a cid_cname.txt
> 
> gcc actually_run.c
> 
> #測試
> //學號找課程
> a D0500030  //有的學號
> a D0915874  //錯的學號
> 
> //課程找學號
> a 1274 //有的課號
> a 1273 //錯的課號
> 
> //課程名稱找學號
> a 程式設計(III)  //有的課程名稱
> a 班級           //錯的課程名稱
