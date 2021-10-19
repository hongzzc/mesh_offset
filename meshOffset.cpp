#include "SurfaceMesh.h"
#include "Eigen\Dense"
#include "Eigen\Eigenvalues"
#include <queue>
#include "SurfaceNormals.h"


using namespace pmp;
using namespace std;

int main()
{
	SurfaceMesh mesh, offsetedMesh;

	mesh.read("C:\\Users\\71530\\Desktop\\小论文\\数据\\一般曲面局部.stl");
	//mesh.read("C:\\Users\\71530\\Desktop\\.stl");

	offsetedMesh = mesh;


	//SurfaceNormals::compute_vertex_normals(offsetedMesh);//turrn
	//SurfaceNormals::vertex_shape_centroid(offsetedMesh);//xiao he 
	SurfaceNormals::vertex_angle_perimeter(offsetedMesh);//gao shan
	//SurfaceNormals::vertex_angle_centroid(offsetedMesh);//gao jian
	//SurfaceNormals::shape_angle_centroid(offsetedMesh);//benwen

	auto v_position = offsetedMesh.get_vertex_property<Point>("v:point");
	auto v_normals = offsetedMesh.get_vertex_property<Normal>("v:normal");

	//auto v_position = mesh.get_vertex_property<Point>("v:point");
	//auto v_normals = mesh.get_vertex_property<Normal>("v:vertex_normal");
	for (Vertex v : offsetedMesh.vertices())
	{
		v_position[v] = v_position[v] + v_normals[v] * 50;
	} 

	SurfaceNormals::compute_face_normals(mesh);
	SurfaceNormals::compute_face_normals(offsetedMesh);




	//使用球体时的顶点法向对比

	auto position = mesh.get_vertex_property<Point>("v:point");

	float angle = 0;
	float angle1 = 0;
	float max_angle = 0;
	float angle_square = 0;
	Point pos;
	int k;
	Normal nor;

	for (int i = 0; i < mesh.vertices_size(); ++i)
	{
		if (true/*!mesh.is_boundary(Vertex(i))*/)
		{
			float denom = sqrt(dot(v_normals[Vertex(i)], v_normals[Vertex(i)]) * dot(position[Vertex(i)], position[Vertex(i)]));
			float cosin = dot(v_normals[Vertex(i)], position[Vertex(i)]) / denom;
			if (cosin < -1.0)
				cosin = -1.0;
			else if (cosin > 1.0)
				cosin = 1.0;

			angle1 = acos(cosin);

			angle1 = angle1 / 3.14 * 180;

			if (angle1 > max_angle)
			{
				max_angle = angle1;
				pos = mesh.position(Vertex(i));
				k = i;
				nor = v_normals[Vertex(i)];
			}
				


			angle_square = angle_square + angle1 * angle1;

			angle = angle + angle1;
		}
	}
	angle = angle / mesh.vertices_size();


	cout << angle << endl;
	cout << max_angle << endl;
	cout << sqrt((angle_square / mesh.vertices_size() - angle * angle)/mesh.vertices_size()) << endl;


	//使用椭圆面时顶点法向对比
	//auto position = mesh.get_vertex_property<Point>("v:point");

	//float angle = 0;
	//float angle1 = 0;
	//float max_angle = 0;
	//float angle_square = 0;
	//float a=64, b=25, c=25; //椭球的三个轴
	//Point pos;
	//int k;
	//for (int i = 0; i < mesh.vertices_size(); ++i)
	//{
	//	Normal normals(0, 0, 0);
	//	normals[0] = 2 * position[Vertex(i)][0] / a;
	//	normals[1] = 2 * position[Vertex(i)][1] / b;
	//	normals[2] = 2 * position[Vertex(i)][2] / c;

	//	if (true/*!mesh.is_boundary(Face(i))*/)
	//	{
	//		float denom = sqrt(dot(v_normals[Vertex(i)], v_normals[Vertex(i)]) * dot(normals, normals));
	//		float cosin = dot(v_normals[Vertex(i)], normals) / denom;
	//		if (cosin < -1.0)
	//			cosin = -1.0;
	//		else if (cosin > 1.0)
	//			cosin = 1.0;

	//		angle1 = acos(cosin);

	//		angle1 = angle1 / 3.14 * 180;

	//		if (angle1 > max_angle)
	//		{
	//			max_angle = angle1;
	//			pos = mesh.position(Vertex(i));
	//			k = i;
	//		}

	//		angle_square = angle_square + angle1 * angle1;

	//		angle = angle + angle1;
	//	}
	//}
	//angle = angle / mesh.vertices_size();

	//cout << pos << endl;
	//cout << k << endl;

	//cout << angle << endl;
	//cout << max_angle << endl;
	//cout << sqrt((angle_square / mesh.vertices_size() - angle * angle)/mesh.vertices_size()) << endl;




	//每个面片法向之间的夹角值

    //SurfaceNormals::compute_face_normals(mesh);
	//SurfaceNormals::compute_face_normals(offsetedMesh);


	//auto nor_mesh = mesh.get_face_property<Normal>("f:normal");
	//auto nor_off_mesh = offsetedMesh.get_face_property<Normal>("f:normal");

	//float angle = 0;
	//float angle1 = 0;
	//float max_angle = 0;
	//float angle_square = 0;
	//for (int i = 0; i < mesh.faces_size(); ++i)
	//{
	//	if (true/*!mesh.is_boundary(Face(i))*/)
	//	{
	//		float denom = sqrt(dot(nor_mesh[Face(i)], nor_mesh[Face(i)]) * dot(nor_off_mesh[Face(i)], nor_off_mesh[Face(i)]));
	//		float cosin = dot(nor_mesh[Face(i)], nor_off_mesh[Face(i)]) / denom;
	//		if (cosin < -1.0)
	//			cosin = -1.0;
	//		else if (cosin > 1.0)
	//			cosin = 1.0;
	//		angle1 = acos(cosin);

	//		angle1 = angle1 / 3.14 * 180;

	//		if (angle1 > max_angle)
	//			max_angle = angle1;


	//		angle_square = angle_square + angle1 * angle1;

	//		angle = angle + angle1;
	//	}
	//}
	//angle = angle / mesh.faces_size();

	//cout << max_angle << endl;
	//cout << angle << endl;
	//cout << sqrt((angle_square / mesh.faces_size() - angle * angle)/mesh.faces_size()) << endl;



	//每个顶点之间的法矢差

	//SurfaceNormals::compute_vertex_normals(mesh);
	//SurfaceNormals::compute_vertex_normals(offsetedMesh);

	//auto nor_mesh = mesh.get_vertex_property<Normal>("v:normal");
	//auto nor_off_mesh = offsetedMesh.get_vertex_property<Normal>("v:normal");

	//float angle = 0;
	//float angle1 = 0;
	//float max_angle = 0;
	//float angle_square = 0;
	//for (int i = 0; i < mesh.vertices_size(); ++i)
	//{
	//	if (true/*!mesh.is_boundary(Face(i))*/)
	//	{
	//		float denom = sqrt(dot(nor_mesh[Vertex(i)], nor_mesh[Vertex(i)]) * dot(nor_off_mesh[Vertex(i)], nor_off_mesh[Vertex(i)]));
	//		float cosin = dot(nor_mesh[Vertex(i)], nor_off_mesh[Vertex(i)]) / denom;
	//		if (cosin < -1.0)
	//			cosin = -1.0;
	//		else if (cosin > 1.0)
	//			cosin = 1.0;
	//		angle1 = acos(cosin);

	//		angle1 = angle1 / 3.14 * 180;

	//		if (angle1 > max_angle)
	//			max_angle = angle1;


	//		angle_square = angle_square + angle1 * angle1;

	//		angle = angle + angle1;
	//	}
	//}
	//angle = angle / mesh.vertices_size();
	//
	//cout << max_angle << endl;
	//cout << angle << endl;
	//cout << sqrt((angle_square / mesh.vertices_size() - angle * angle) / mesh.vertices_size()) << endl;


	mesh.write("C:\\Users\\71530\\Desktop\\yuanshi.obj");
	offsetedMesh.write("C:\\Users\\71530\\Desktop\\pianzhi.obj");

	return 0;
}

