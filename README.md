# This is a ray tracer program
## support features:
-- anti-aliasing
-- depth of field
-- soft shadows
-- environment mapping
-- texture mapping
-- glossy reflection

## How to use: 
- To run the code after making file, type the command like below in terminal: 
  ./raytracer [width height] [-s -g -e -a -d -t] 
- where -s for soft-shadow, -g for glossy reflection, -e for environment mapping, -a for anti-alias, -d for depth of field and -t for texture mapping. 
- if no resolution specified, image size is set by 320x240 by default.
the output images are saved under the folder 'results'.

## Below are some ray tracing output:


-- Raw output vs Anti alias:

![original](https://github.com/liyue1163/ray-tracer/blob/master/results/origin/view1.bmp)
![anti alias](https://github.com/liyue1163/ray-tracer/blob/master/results/anti-alias/view1.bmp)

-- anti alias

![anti alias](https://github.com/liyue1163/ray-tracer/blob/master/results/anti-alias/view2.bmp)

-- Raw output vs Depth of field:

![original](https://github.com/liyue1163/ray-tracer/blob/master/results/origin/view1.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/Depth-of-Field/dof-view1.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/origin/view2.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/Depth-of-Field/dof-view2.bmp)

-- Raw output vs soft shadows:

![original](https://github.com/liyue1163/ray-tracer/blob/master/results/origin/view1.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/soft-shadow/view1.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/origin/view2.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/soft-shadow/view2.bmp)

-- Raw output vs Glossy reflectoin:

![original](https://github.com/liyue1163/ray-tracer/blob/master/results/origin/view1.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/glossy/view1.JPG)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/origin/view2.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/glossy/view2.JPG)

-- Environment mapping & Texture mapping:

![original](https://github.com/liyue1163/ray-tracer/blob/master/results/environment-mapping/view1.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/environment-mapping/view2.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/texture-mapping/view1.bmp)
![original](https://github.com/liyue1163/ray-tracer/blob/master/results/texture-mapping/view2.bmp)

