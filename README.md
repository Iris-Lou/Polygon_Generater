# Polygon_Generater
  This C++ project aims to create polygons by inputing a file that contains neccessary information of the polygons. We can also get the intersection and union of circular and irregular polygons through the programs, and obtain the perimeter and area of various shapes. 
    
中文版题目：
定义一个点类Point，提供打印功能Print()。
定义一个边类Edge，包括一条边的两个Point端点
提供求长度Length()和打印Print()纯虚函数。Edge派生出直线边StraightEdge和圆弧边ArcEdge，ArcEdge除了边的两个端点之外，还包含对应的圆心（Point）
定义一个抽象基类Shape。Shape派生出圆类Circle，Circle派生出扇形Sector类。Shape派生出类多边形类MyPolygon。
提供操作符重载函数，支持两个Shape对象s1,s2的与和或（即交和并）操作：s1 & s2， s1 | s2，返回一个新的Shape对象。支持连续操作比如s1 & s2 | s3
实现一个ShapeFile类，读取一个文件Shapes.txt。提供一个void Generate()函数，为Shape对象两两进行&和|操作，产生新的Shape对象。为ShapeFile提供一个Print函数。
