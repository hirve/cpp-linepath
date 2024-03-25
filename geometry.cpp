#include "geometry.h"

using namespace geometry;

double pointsDistance2 (Point2D p1, Point2D p2) {
  double xDist = p1.x - p2.x, yDist = p1.y - p2.y;
  return xDist * xDist + yDist * yDist;
}

bool isPointLineDistanceLessThan (Point2D p, Line line, double r) {
  double r2 = r * r;
  if (line[0].x == line[1].x && line[0].y == line[1].y) {
    return pointsDistance2(p, line[0]) < r2;
  } else {
    double lineLen2 = pointsDistance2(line[0], line[1]);
    double t = ((p.x - line[0].x) * (line[1].x - line[0].x) + (p.y - line[0].y) * (line[1].y - line[0].y)) / lineLen2;
    double t01 = std::max(0.0, std::min(1.0, t));
    Point2D p2 = { line[0].x + t01 * (line[1].x - line[0].x), line[0].y + t01 * (line[1].y - line[0].y) };
    return pointsDistance2(p, p2) < r2;
  }
}

BoundindBox2D calcBoundindBox (Path2D path) {
  BoundindBox2D box = { { path[0].x, path[0].x }, { path[0].y, path[0].y } };
  for (size_t i = 1; i < path.size(); i++) {
    box.x.min = std::min(box.x.min, path[i].x);
    box.x.max = std::max(box.x.max, path[i].x);
    box.y.min = std::min(box.y.min, path[i].y);
    box.y.max = std::max(box.y.max, path[i].y);
  }
  return box;
}

EnclosedShape::EnclosedShape (Path2D path) {
  this->path = path;
  Point2D lastPoint = path[path.size() - 1];
  if (path[0].x != lastPoint.x || path[0].y != lastPoint.y) {
    this->path.push_back({ path[0].x, path[0].y });
  }
  if (this->path.size() > 0) {
    this->box = calcBoundindBox(this->path);
  }
}

Path2D EnclosedShape::getPath () {
  return this->path;
}

BoundindBox2D EnclosedShape::getBoundindBox () {
  return this->box;
}

bool EnclosedShape::isInside (Point2D p) { // todo exactify edge cases or/and keep fast
  uint count = 0;
  Point2D prevP = this->path[0];
  for (size_t i = 1; i < this->path.size(); i++) {
    Line line = { prevP, this->path[i] };
      if ((line[0].y < p.y && line[1].y >= p.y) || (line[0].y >= p.y && line[1].y < p.y)) {
        if (line[0].x <= p.x || line[1].x <= p.x) {
          if ((line[0].x <= p.x && line[1].x <= p.x)
                || (p.y - line[0].y) / (line[1].y - line[0].y) * (line[1].x - line[0].x) + line[0].x <= p.x) {
            count ++;
          }
        }
      }
    prevP = this->path[i];
  }
  return (count & 1) == 1;
}

bool EnclosedShape::isCloserThan (Point2D p, double r) {
  Point2D prevP = this->path[0];
  for (size_t i = 1; i < this->path.size(); i++) {
    Line line = { prevP, this->path[i] };
      if (!(line[0].x < p.x - r && line[1].x < p.x - r)
            && !(line[0].x > p.x + r && line[1].x > p.x + r)
            && !(line[0].y < p.y - r && line[1].y < p.y - r)
            && !(line[0].y > p.y + r && line[1].y > p.y + r)) {
        if (isPointLineDistanceLessThan(p, line, r)) {
            return true;
        }
      }
    prevP = this->path[i];
  }
  return false;
}
