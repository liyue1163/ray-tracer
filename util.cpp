/***********************************************************

	Starter code for Assignment 3
	
	Implementations of util.h	

***********************************************************/

#include "util.h"
  
Point3D::Point3D() {
	m_data[0] = 0.0;
	m_data[1] = 0.0;
	m_data[2] = 0.0;
}

Point3D::Point3D(double x, double y, double z) { 
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
}

Point3D::Point3D(const Point3D& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
}

Point3D& Point3D::operator =(const Point3D& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
	return *this;
}

double& Point3D::operator[](int i) {
	return m_data[i];
}

double Point3D::operator[](int i) const {
	return m_data[i];
}
	
Vector3D::Vector3D() {
	m_data[0] = 0.0;
	m_data[1] = 0.0;
	m_data[2] = 0.0;
}

Vector3D::Vector3D(double x, double y, double z) { 
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
}

Vector3D::Vector3D(const Vector3D& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
}

Vector3D& Vector3D::operator =(const Vector3D& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
	return *this;
}

double& Vector3D::operator[](int i) {
	return m_data[i];
}
double Vector3D::operator[](int i) const {
	return m_data[i];
}

double Vector3D::length() const
{
	return sqrt(dot(*this));
}

double Vector3D::normalize() {
	double denom = 1.0;
	double x = (m_data[0] > 0.0) ? m_data[0] : -m_data[0];
	double y = (m_data[1] > 0.0) ? m_data[1] : -m_data[1];
	double z = (m_data[2] > 0.0) ? m_data[2] : -m_data[2];

	if(x > y) {
		if(x > z) {
			if(1.0 + x > 1.0) {
				y = y / x;
				z = z / x;
				denom = 1.0 / (x * sqrt(1.0 + y*y + z*z));
			}
		} else { /* z > x > y */ 
			if(1.0 + z > 1.0) {
				y = y / z;
				x = x / z;
				denom = 1.0 / (z * sqrt(1.0 + y*y + x*x));
			}
		}
	} else {
		if(y > z) {
			if(1.0 + y > 1.0) {
				z = z / y;
				x = x / y;
				denom = 1.0 / (y * sqrt(1.0 + z*z + x*x));
			}
		} else { /* x < y < z */
			if(1.0 + z > 1.0) {
				y = y / z;
				x = x / z;
				denom = 1.0 / (z * sqrt(1.0 + y*y + x*x));
			}
		}
	}

	if(1.0 + x + y + z > 1.0) {
		m_data[0] *= denom;
		m_data[1] *= denom;
		m_data[2] *= denom;
		return 1.0 / denom;
	}

	return 0.0;
}

double Vector3D::dot(const Vector3D& other) const
{
	return m_data[0]*other.m_data[0] + 
		m_data[1]*other.m_data[1] + 
		m_data[2]*other.m_data[2];
}

double Vector3D::norm() const
{
	double norm_sqaure = this->dot(*this);
	return sqrt(norm_sqaure);
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
	return Vector3D(
			m_data[1]*other[2] - m_data[2]*other[1],
			m_data[2]*other[0] - m_data[0]*other[2],
			m_data[0]*other[1] - m_data[1]*other[0]);
}

Vector3D operator *(double s, const Vector3D& v)
{
  return Vector3D(s*v[0], s*v[1], s*v[2]);
}

Vector3D operator +(const Vector3D& u, const Vector3D& v)
{
  return Vector3D(u[0]+v[0], u[1]+v[1], u[2]+v[2]);
}

Point3D operator +(const Point3D& u, const Vector3D& v)
{
  return Point3D(u[0]+v[0], u[1]+v[1], u[2]+v[2]);
}

Vector3D operator -(const Point3D& u, const Point3D& v)
{
  return Vector3D(u[0]-v[0], u[1]-v[1], u[2]-v[2]);
}

Vector3D operator -(const Vector3D& u, const Vector3D& v)
{
  return Vector3D(u[0]-v[0], u[1]-v[1], u[2]-v[2]);
}

Vector3D operator -(const Vector3D& u)
{
  return Vector3D(-u[0], -u[1], -u[2]);
}

Point3D operator -(const Point3D& u, const Vector3D& v)
{
  return Point3D(u[0]-v[0], u[1]-v[1], u[2]-v[2]);
}

Vector3D cross(const Vector3D& u, const Vector3D& v) 
{
  return u.cross(v);
}

std::ostream& operator <<(std::ostream& s, const Point3D& p)
{
  return s << "p(" << p[0] << "," << p[1] << "," << p[2] << ")";
}

std::ostream& operator <<(std::ostream& s, const Vector3D& v)
{
  return s << "v(" << v[0] << "," << v[1] << "," << v[2] << ")";
}

double operator / (const Vector3D& u, const Vector3D& v){
	double t = 0;
	for (int i = 0; i < 3; i++){
		if (v[i] != 0.0){
			t = u[i] / v[i];
			break;
		}
	}
	if ((u[0] != t * v[0]) || (u[1] != t * v[1]) || (u[2] != t * v[2])){
		return 0.0;
	}
	return t;
}

Color::Color() {
	m_data[0] = 0.0;
	m_data[1] = 0.0;
	m_data[2] = 0.0;
}

Color::Color(double r, double g, double b) { 
	m_data[0] = r;
	m_data[1] = g;
	m_data[2] = b;
}

Color::Color(const Color& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
}

Color& Color::operator =(const Color& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
	return *this;
}

Color Color::operator *(const Color& other) {
	return Color(m_data[0]*other.m_data[0], 
		m_data[1]*other.m_data[1], 
		m_data[2]*other.m_data[2]);
}

double& Color::operator[](int i) {
	return m_data[i];
}
double Color::operator[](int i) const {
	return m_data[i];
}

void Color::clamp() {
	for (int i = 0; i < 3; i++) {
		if (m_data[i] > 1.0) m_data[i] = 1.0; 
		if (m_data[i] < 0.0) m_data[i] = 0.0; 
	}
}

Color operator *(double s, const Color& c)
{
  return Color(s*c[0], s*c[1], s*c[2]);
}

Color operator *(const Color& c, double s)
{
  return Color(s*c[0], s*c[1], s*c[2]);
}

Color operator +(const Color& u, const Color& v)
{
  return Color(u[0]+v[0], u[1]+v[1], u[2]+v[2]);
}

std::ostream& operator <<(std::ostream& s, const Color& c)
{
  return s << "c(" << c[0] << "," << c[1] << "," << c[2] << ")";
}

Vector4D::Vector4D() {
	m_data[0] = 0.0;
	m_data[1] = 0.0;
	m_data[2] = 0.0;
	m_data[3] = 0.0;
}

Vector4D::Vector4D(double w, double x, double y, double z) { 
	m_data[0] = w;
	m_data[1] = x;
	m_data[2] = y;
	m_data[3] = z;
}

Vector4D::Vector4D(const Vector4D& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
	m_data[3] = other.m_data[3];
}

Vector4D& Vector4D::operator =(const Vector4D& other) {
	m_data[0] = other.m_data[0];
	m_data[1] = other.m_data[1];
	m_data[2] = other.m_data[2];
	m_data[3] = other.m_data[3];
	return *this;
}

double& Vector4D::operator[](int i) {
	return m_data[i];
}
double Vector4D::operator[](int i) const {
	return m_data[i];
}

Matrix4x4::Matrix4x4() {
	for (int i = 0; i < 16; i++) 
		m_data[i] = 0.0; 
	m_data[0] = 1.0;
	m_data[5] = 1.0;
	m_data[10] = 1.0;
	m_data[15] = 1.0;
}

Matrix4x4::Matrix4x4(const Matrix4x4& other) {
	for (int i = 0; i < 16; i++) 
		m_data[i] = other.m_data[i]; 
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) {
	for (int i = 0; i < 16; i++) 
		m_data[i] = other.m_data[i]; 
	return *this;
}

Vector4D Matrix4x4::getRow(int row) const {
	return Vector4D(m_data[4*row], m_data[4*row+1], m_data[4*row+2], 
			m_data[4*row+3]);
}

double* Matrix4x4::getRow(int row) {
	return (double*)m_data + 4*row;
}

Vector4D Matrix4x4::getColumn(int col) const {
	return Vector4D(m_data[col], m_data[4+col], m_data[8+col], 
			m_data[12+col]);
}

Vector4D Matrix4x4::operator[](int row) const {
	return getRow(row);
}

double* Matrix4x4::operator[](int row) {
	return getRow(row);
}

Matrix4x4 Matrix4x4::transpose() const {
	Matrix4x4 M; 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			M[i][j] = (*this)[j][i]; 
		}
	}
	return M; 
}
 
Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b) {
	Matrix4x4 ret;

	for(size_t i = 0; i < 4; ++i) {
		Vector4D row = a.getRow(i);

		for(size_t j = 0; j < 4; ++j) {
			ret[i][j] = row[0] * b[0][j] + row[1] * b[1][j] + 
				row[2] * b[2][j] + row[3] * b[3][j];
		}
	}

	return ret;
}

Vector3D operator *(const Matrix4x4& M, const Vector3D& v) {
	return Vector3D(
			v[0] * M[0][0] + v[1] * M[0][1] + v[2] * M[0][2],
			v[0] * M[1][0] + v[1] * M[1][1] + v[2] * M[1][2],
			v[0] * M[2][0] + v[1] * M[2][1] + v[2] * M[2][2]);
}

Point3D operator *(const Matrix4x4& M, const Point3D& p) {
	return Point3D(
			p[0] * M[0][0] + p[1] * M[0][1] + p[2] * M[0][2] + M[0][3],
			p[0] * M[1][0] + p[1] * M[1][1] + p[2] * M[1][2] + M[1][3],
			p[0] * M[2][0] + p[1] * M[2][1] + p[2] * M[2][2] + M[2][3]);
}

Vector3D transNorm(const Matrix4x4& M, const Vector3D& n) {
	return Vector3D(
			n[0] * M[0][0] + n[1] * M[1][0] + n[2] * M[2][0],
			n[0] * M[0][1] + n[1] * M[1][1] + n[2] * M[2][1],
			n[0] * M[0][2] + n[1] * M[1][2] + n[2] * M[2][2]);
}

std::ostream& operator <<(std::ostream& os, const Matrix4x4& M) {
	return os << "[" << M[0][0] << " " << M[0][1] << " " 
		<< M[0][2] << " " << M[0][3] << "]" << std::endl
		<< "[" << M[1][0] << " " << M[1][1] << " " 
		<< M[1][2] << " " << M[1][3] << "]" << std::endl
		<< "[" << M[2][0] << " " << M[2][1] << " " 
		<< M[2][2] << " " << M[2][3] << "]" << std::endl
		<< "[" << M[3][0] << " " << M[3][1] << " " 
		<< M[3][2] << " " << M[3][3] << "]";
}

void Image::setPixelBuffer(char col, unsigned char * colArray){
	int numBytes = width * height * sizeof(unsigned char);
	switch(col) {
    case 'r':{
    	memcpy((void *)rbuffer, (const void*)colArray, numBytes);

    	break;
    } 
    case 'g':{
    	memcpy((void *)gbuffer, (const void*)colArray, numBytes);
    	break;
    } 
    case 'b':{
    	memcpy((void *)bbuffer, (const void*)colArray, numBytes);
    	break;
    } 
  }	
}

void Image::getColorAtPixel(int u, int v, Color& col){
		col[0] = rbuffer[v*width+u] / 255.0;
		col[1] = gbuffer[v*width+u] / 255.0;
		col[2] = bbuffer[v*width+u] / 255.0; 
}

void createEnvImages(vector<Image*>& envImages, string file_in_dir, int width, int height){
	unsigned char * rarray;
	unsigned char * garray;
	unsigned char * barray;
	string file_in_name;
	// bmp_read will modify value of width and height that put in
	long unsigned int width2;
	long int height2;

	// index 0: posx
	file_in_name = file_in_dir + "/posx.bmp";
 	width2 = (long unsigned int)width;
	height2 = (long int)height;
	bmp_read(file_in_name.c_str(), &width2, &height2, &rarray, &garray, &barray);	
	Image * posx_image = new Image(width, height, rarray, garray, barray);
	envImages.push_back(posx_image);

	// index 1: negx
	file_in_name = file_in_dir + "/negx.bmp";
	width2 = (long unsigned int)width;
	height2 = (long int)height;
	bmp_read(file_in_name.c_str(), &width2, &height2, &rarray, &garray, &barray);	
	Image * negx_image = new Image(width, height, rarray, garray, barray);
	envImages.push_back(negx_image);

	// index 2: posy
	file_in_name = file_in_dir + "/posy.bmp";
	width2 = (long unsigned int)width;
	height2 = (long int)height;
	bmp_read(file_in_name.c_str(), &width2, &height2, &rarray, &garray, &barray);	
	Image * posy_image = new Image(width, height, rarray, garray, barray);
	envImages.push_back(posy_image);

	// index 3: negy
	file_in_name = file_in_dir + "/negy.bmp";
	width2 = (long unsigned int)width;
	height2 = (long int)height;
	bmp_read(file_in_name.c_str(), &width2, &height2, &rarray, &garray, &barray);	
	Image * negy_image = new Image(width, height, rarray, garray, barray);
	envImages.push_back(negy_image);

	// index 4: posz
	file_in_name = file_in_dir + "/posz.bmp";
	width2 = (long unsigned int)width;
	height2 = (long int)height;
	bmp_read(file_in_name.c_str(), &width2, &height2, &rarray, &garray, &barray);	
	Image * posz_image = new Image(width, height, rarray, garray, barray);
	envImages.push_back(posz_image);

	// index 5: negz
	file_in_name = file_in_dir + "/negz.bmp";
	width2 = (long unsigned int)width;
	height2 = (long int)height;
	bmp_read(file_in_name.c_str(), &width2, &height2, &rarray, &garray, &barray);	
	Image * negz_image = new Image(width, height, rarray, garray, barray);
	envImages.push_back(negz_image);
}

void createTextureImages(vector<Image*>& textureImages, vector<string> file_in_names, vector<int> widths, vector<int> heights){
	unsigned char * rarray;
	unsigned char * garray;
	unsigned char * barray;
	string file_in_name;
	int width;
	int height;
	long unsigned int width2;
	long int height2;
	Image * image;

	for (int i = 0; i < file_in_names.size(); i++){
		file_in_name = file_in_names[i];
		width = widths[i];
		height = heights[i];
		if (widths[i] != 0){
			width2 = (long unsigned int)width;
			height2 = (long int)height;
			bmp_read(file_in_name.c_str(), &width2, &height2, &rarray, &garray, &barray);	
			image = new Image(width, height, rarray, garray, barray);
		}else{
			image = new Image(width, height);
		}
		textureImages.push_back(image);	
	}
}

void xyz_to_iuv(double x, double y, double z, int *index, double *u, double *v)
{
  double absX = fabs(x);
  double absY = fabs(y);
  double absZ = fabs(z);

  int isXPositive = x > 0 ? 1 : 0;
  int isYPositive = y > 0 ? 1 : 0;
  int isZPositive = z > 0 ? 1 : 0;

  double maxAxis, uc, vc;

  // POSITIVE X
  if (isXPositive && absX >= absY && absX >= absZ) {
    // u (0 to 1) goes from +z to -z
    // v (0 to 1) goes from -y to +y
    maxAxis = absX;
    uc = -z;
    vc = y;
    *index = 0;
  }
  // NEGATIVE X
  if (!isXPositive && absX >= absY && absX >= absZ) {
    // u (0 to 1) goes from -z to +z
    // v (0 to 1) goes from -y to +y
    maxAxis = absX;
    uc = z;
    vc = y;
    *index = 1;
  }
  // POSITIVE Y
  if (isYPositive && absY >= absX && absY >= absZ) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from +z to -z
    maxAxis = absY;
    uc = x;
    vc = -z;
    *index = 2;
  }
  // NEGATIVE Y
  if (!isYPositive && absY >= absX && absY >= absZ) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from -z to +z
    maxAxis = absY;
    uc = x;
    vc = z;
    *index = 3;
  }
  // POSITIVE Z
  if (isZPositive && absZ >= absX && absZ >= absY) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from -y to +y
    maxAxis = absZ;
    uc = x;
    vc = y;
    *index = 4;
  }
  // NEGATIVE Z
  if (!isZPositive && absZ >= absX && absZ >= absY) {
    // u (0 to 1) goes from +x to -x
    // v (0 to 1) goes from -y to +y
    maxAxis = absZ;
    uc = -x;
    vc = y;
    *index = 5;
  }

  // Convert range from -1 to 1 to 0 to 1
  *u = 0.5f * (uc / maxAxis + 1.0f);
  *v = 0.5f * (vc / maxAxis + 1.0f);
}


void xyz_to_uv(Point3D intersection, Point3D center, double * u, double * v){
	double radius = (intersection - center).norm();
	double theta = acos((intersection[2] - center[2]) / radius); // longitude, theta in [0, pi]
	double phi = atan((intersection[1] - center[1]) / (intersection[0] - center[0])); // latitude, phi in [-pi, pi]
	double pi = 3.1415926535897;
	*u = theta / pi;
	*v = (phi + pi) / (2 * pi);
}
