#include "embree.h"

#include <iostream>
#include <random>

#include "SimpleRayTracer.h"

void embree_error(void * ptr, RTCError error, const char * str)
{
	fprintf(stderr, "EMBREE ERROR: %s\n", str);
}

embree::embree()
{
	device = rtcNewDevice(NULL);
	rtcSetDeviceErrorFunction(device, embree_error, NULL);

	scene = rtcNewScene(device);
}

embree::~embree()
{
	rtcReleaseScene(scene);
	rtcReleaseDevice(device);
}

void embree::build_bvh()
{
	rtcCommitScene(scene);
}

unsigned embree::add_sphere(const glm::vec4 & xyzr)
{
	RTCGeometry geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_SPHERE_POINT);

	glm::vec4 * pxyzr = (glm::vec4 *) rtcSetNewGeometryBuffer(geom,
															RTC_BUFFER_TYPE_VERTEX, 0,
															RTC_FORMAT_FLOAT4, 4 * sizeof(float), 1);
	*pxyzr = xyzr;

	rtcCommitGeometry(geom);
	
	unsigned geom_id = rtcAttachGeometry(scene, geom);
	rtcReleaseGeometry(geom);
	
	return geom_id;
}

unsigned embree::add_mesh(const DrawableShape & mesh, const glm::mat4 & model_matrix)
{
	RTCGeometry geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

	const std::vector<glm::vec3> & positions = mesh.getPositions();
	glm::vec3 * vertices = (glm::vec3 *) rtcSetNewGeometryBuffer(geom,
																RTC_BUFFER_TYPE_VERTEX, 0,
																RTC_FORMAT_FLOAT3, 3 * sizeof(float),
																positions.size());

	const std::vector<glm::uvec3> & faces = mesh.getFaces();
	glm::uvec3 * tri_idxs = (glm::uvec3 *) rtcSetNewGeometryBuffer(geom,
																RTC_BUFFER_TYPE_INDEX, 0,
																RTC_FORMAT_UINT3, 3 * sizeof(int),
																faces.size());

	for(unsigned i = 0; i < positions.size(); i++)
		vertices[i] = glm::vec3(model_matrix * glm::vec4(positions[i], 1.f));
	
	for(unsigned i = 0; i < faces.size(); i++)
		tri_idxs[i] = faces[i];

	rtcCommitGeometry(geom);
	
	unsigned geom_id = rtcAttachGeometry(scene, geom);
	rtcReleaseGeometry(geom);
	
	return geom_id;
}

std::future<float*> embree::cast_rays(const glm::uvec2 & windows_size, const Camera & cam, const unsigned & samples)
{
    auto simpleTracer = std::make_shared<SimpleRayTracer>(windows_size.x, windows_size.y, scene);
    return simpleTracer->start(cam, samples);
}

bool embree::intersect(ray_hit & r)
{
	RTCIntersectContext context;
	rtcInitIntersectContext(&context);
	rtcIntersect1(scene, &context, &r);

	return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
}

