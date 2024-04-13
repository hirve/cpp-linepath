#pragma once
#include <vector>

namespace geometry {

  struct Point2D { double x; double y; };
  struct BoundindRange { double min; double max; };
  struct BoundindBox2D { BoundindRange x; BoundindRange y; };
  typedef std::vector<Point2D> Path2D;
  typedef Point2D Line[2];

  class EnclosedShape {
    public:
      EnclosedShape ();
      ~EnclosedShape ();
      EnclosedShape (Path2D path);
      Path2D getPath ();
      BoundindBox2D getBoundindBox ();
      bool isInside (Point2D p);
      bool isCloserThan (Point2D p, double r);

    private:
      Path2D path;
      BoundindBox2D box;
  };
}
