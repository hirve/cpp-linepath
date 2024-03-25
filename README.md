# CPP Linepath

It's just a fast version of my Python library of linepath geometry, which is the addition for https://github.com/hirve/py-functional-mill to limit cut area by a shape, where the shape is a polyline path.

### Creating the Shape
```cpp
  EnclosedShape* shape = new EnclosedShape({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } });
```

### Getting Path
```cpp
  Path2D path = shape->getPath();
```

### Getting Bounding Box
```cpp
  BoundindBox2D box = shape->getBoundindBox();
```

### Is the Point inside the Shape
```cpp
  std::cout << "Is inside, should be 1 -> " << shape->isInside({ 0.5, 0.5 }) << "\n";
  std::cout << "Is inside, should be 0 -> " << shape->isInside({ -0.1, 0.5 }) << '\n';
```

### Is the point closer than R - to offset the Cutting Tool radius
```cpp
  std::cout << "Is closer, should be 0 -> " << shape->isCloserThan({ 0.5, 0.5 }, 0.1) << "\n";
  std::cout << "Is closer, should be 1 -> " << shape->isCloserThan({ -0.05, 0.5 }, 0.1) << "\n";
```

## Important Edge Cases
- When the point is on the shape edge -> this case is not significant for my CNC milling app, because in raster based application such little distance doesn't make sense. But if you want to make any activity, based on the shape source path, you should be aware that the **isInside** method will give unexpected results.
