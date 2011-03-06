//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include <float.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "Recast.h"
#include "RecastAlloc.h"
#include "RecastAssert.h"

float rcSqrt(float x)
{
	return sqrtf(x);
}


void rcContext::log(const rcLogCategory category, const char* format, ...)
{
	if (!m_logEnabled)
		return;
	static const int MSG_SIZE = 512;
	char msg[MSG_SIZE];
	va_list ap;
	va_start(ap, format);
	int len = vsnprintf(msg, MSG_SIZE, format, ap);
	if (len >= MSG_SIZE)
	{
		len = MSG_SIZE-1;
		msg[MSG_SIZE-1] = '\0';
	}
	va_end(ap);
	doLog(category, msg, len);
}

rcHeightfield* rcAllocHeightfield()
{
	rcHeightfield* hf = (rcHeightfield*)rcAlloc(sizeof(rcHeightfield), RC_ALLOC_PERM);
	memset(hf, 0, sizeof(rcHeightfield));
	return hf;
}

void rcFreeHeightField(rcHeightfield* hf)
{
	if (!hf) return;
	// Delete span array.
	rcFree(hf->spans);
	// Delete span pools.
	while (hf->pools)
	{
		rcSpanPool* next = hf->pools->next;
		rcFree(hf->pools);
		hf->pools = next;
	}
	rcFree(hf);
}

rcCompactHeightfield* rcAllocCompactHeightfield()
{
	rcCompactHeightfield* chf = (rcCompactHeightfield*)rcAlloc(sizeof(rcCompactHeightfield), RC_ALLOC_PERM);
	memset(chf, 0, sizeof(rcCompactHeightfield));
	return chf;
}

void rcFreeCompactHeightfield(rcCompactHeightfield* chf)
{
	if (!chf) return;
	rcFree(chf->cells);
	rcFree(chf->spans);
	rcFree(chf->dist);
	rcFree(chf->areas);
	rcFree(chf);
}


rcHeightfieldLayerSet* rcAllocHeightfieldLayerSet()
{
	rcHeightfieldLayerSet* lset = (rcHeightfieldLayerSet*)rcAlloc(sizeof(rcHeightfieldLayerSet), RC_ALLOC_PERM);
	memset(lset, 0, sizeof(rcHeightfieldLayerSet));
	return lset;
}

void rcFreeHeightfieldLayerSet(rcHeightfieldLayerSet* lset)
{
	if (!lset) return;
	for (int i = 0; i < lset->nlayers; ++i)
	{
		rcFree(lset->layers[i].heights);
		rcFree(lset->layers[i].areas);
		rcFree(lset->layers[i].regs);
		rcFree(lset->layers[i].portals);
	}
	rcFree(lset->layers);
	rcFree(lset);
}


rcLayerContourSet* rcAllocLayerContourSet()
{
	rcLayerContourSet* cset = (rcLayerContourSet*)rcAlloc(sizeof(rcLayerContourSet), RC_ALLOC_PERM);
	memset(cset, 0, sizeof(rcLayerContourSet));
	return cset;
}

void rcFreeLayerContourSet(rcLayerContourSet* cset)
{
	if (!cset) return;
	for (int i = 0; i < cset->nconts; ++i)
	{
		rcFree(cset->conts[i].verts);
//		rcFree(cset->conts[i].rverts);
	}
	rcFree(cset->conts);
	rcFree(cset);
}

rcLayerPolyMesh* rcAllocLayerPolyMesh()
{
	rcLayerPolyMesh* lmesh = (rcLayerPolyMesh*)rcAlloc(sizeof(rcLayerPolyMesh), RC_ALLOC_PERM);
	memset(lmesh, 0, sizeof(rcLayerPolyMesh));
	return lmesh;
}

void rcFreeLayerPolyMesh(rcLayerPolyMesh* lmesh)
{
	if (!lmesh) return;
	rcFree(lmesh->verts);
	rcFree(lmesh->polys);
	rcFree(lmesh->flags);
	rcFree(lmesh->areas);
	rcFree(lmesh);
}



rcContourSet* rcAllocContourSet()
{
	rcContourSet* cset = (rcContourSet*)rcAlloc(sizeof(rcContourSet), RC_ALLOC_PERM);
	memset(cset, 0, sizeof(rcContourSet));
	return cset;
}

void rcFreeContourSet(rcContourSet* cset)
{
	if (!cset) return;
	for (int i = 0; i < cset->nconts; ++i)
	{
		rcFree(cset->conts[i].verts);
		rcFree(cset->conts[i].rverts);
	}
	rcFree(cset->conts);
	rcFree(cset);
}

rcPolyMesh* rcAllocPolyMesh()
{
	rcPolyMesh* pmesh = (rcPolyMesh*)rcAlloc(sizeof(rcPolyMesh), RC_ALLOC_PERM);
	memset(pmesh, 0, sizeof(rcPolyMesh));
	return pmesh;
}

void rcFreePolyMesh(rcPolyMesh* pmesh)
{
	if (!pmesh) return;
	rcFree(pmesh->verts);
	rcFree(pmesh->polys);
	rcFree(pmesh->regs);
	rcFree(pmesh->flags);
	rcFree(pmesh->areas);
	rcFree(pmesh);
}

rcPolyMeshDetail* rcAllocPolyMeshDetail()
{
	rcPolyMeshDetail* dmesh = (rcPolyMeshDetail*)rcAlloc(sizeof(rcPolyMeshDetail), RC_ALLOC_PERM);
	memset(dmesh, 0, sizeof(rcPolyMeshDetail));
	return dmesh;
}

void rcFreePolyMeshDetail(rcPolyMeshDetail* dmesh)
{
	if (!dmesh) return;
	rcFree(dmesh->meshes);
	rcFree(dmesh->verts);
	rcFree(dmesh->tris);
	rcFree(dmesh);
}


void rcCalcBounds(const float* verts, int nv, float* bmin, float* bmax)
{
	// Calculate bounding box.
	rcVcopy(bmin, verts);
	rcVcopy(bmax, verts);
	for (int i = 1; i < nv; ++i)
	{
		const float* v = &verts[i*3];
		rcVmin(bmin, v);
		rcVmax(bmax, v);
	}
}

void rcCalcGridSize(const float* bmin, const float* bmax, float cs, int* w, int* h)
{
	*w = (int)((bmax[0] - bmin[0])/cs+0.5f);
	*h = (int)((bmax[2] - bmin[2])/cs+0.5f);
}

bool rcCreateHeightfield(rcContext* /*ctx*/, rcHeightfield& hf, int width, int height,
						 const float* bmin, const float* bmax,
						 float cs, float ch)
{
	// TODO: VC complains about unref formal variable, figure out a way to handle this better.
//	rcAssert(ctx);
	
	hf.width = width;
	hf.height = height;
	rcVcopy(hf.bmin, bmin);
	rcVcopy(hf.bmax, bmax);
	hf.cs = cs;
	hf.ch = ch;
	hf.spans = (rcSpan**)rcAlloc(sizeof(rcSpan*)*hf.width*hf.height, RC_ALLOC_PERM);
	if (!hf.spans)
		return false;
	memset(hf.spans, 0, sizeof(rcSpan*)*hf.width*hf.height);
	return true;
}

static void calcTriNormal(const float* v0, const float* v1, const float* v2, float* norm)
{
	float e0[3], e1[3];
	rcVsub(e0, v1, v0);
	rcVsub(e1, v2, v0);
	rcVcross(norm, e0, e1);
	rcVnormalize(norm);
}

void rcMarkWalkableTriangles(rcContext* /*ctx*/, const float walkableSlopeAngle,
							 const float* verts, int /*nv*/,
							 const int* tris, int nt,
							 unsigned char* areas)
{
	// TODO: VC complains about unref formal variable, figure out a way to handle this better.
//	rcAssert(ctx);
	
	const float walkableThr = cosf(walkableSlopeAngle/180.0f*RC_PI);

	float norm[3];
	
	for (int i = 0; i < nt; ++i)
	{
		const int* tri = &tris[i*3];
		calcTriNormal(&verts[tri[0]*3], &verts[tri[1]*3], &verts[tri[2]*3], norm);
		// Check if the face is walkable.
		if (norm[1] > walkableThr)
			areas[i] = RC_WALKABLE_AREA;
	}
}

void rcClearUnwalkableTriangles(rcContext* /*ctx*/, const float walkableSlopeAngle,
								const float* verts, int /*nv*/,
								const int* tris, int nt,
								unsigned char* areas)
{
	// TODO: VC complains about unref formal variable, figure out a way to handle this better.
//	rcAssert(ctx);
	
	const float walkableThr = cosf(walkableSlopeAngle/180.0f*RC_PI);
	
	float norm[3];
	
	for (int i = 0; i < nt; ++i)
	{
		const int* tri = &tris[i*3];
		calcTriNormal(&verts[tri[0]*3], &verts[tri[1]*3], &verts[tri[2]*3], norm);
		// Check if the face is walkable.
		if (norm[1] <= walkableThr)
			areas[i] = RC_NULL_AREA;
	}
}

int rcGetHeightFieldSpanCount(rcContext* /*ctx*/, rcHeightfield& hf)
{
	// TODO: VC complains about unref formal variable, figure out a way to handle this better.
//	rcAssert(ctx);
	
	const int w = hf.width;
	const int h = hf.height;
	int spanCount = 0;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			for (rcSpan* s = hf.spans[x + y*w]; s; s = s->next)
			{
				if (s->area != RC_NULL_AREA)
					spanCount++;
			}
		}
	}
	return spanCount;
}

bool rcBuildCompactHeightfield(rcContext* ctx, const int walkableHeight, const int walkableClimb,
							   rcHeightfield& hf, rcCompactHeightfield& chf)
{
	rcAssert(ctx);
	
	ctx->startTimer(RC_TIMER_BUILD_COMPACTHEIGHTFIELD);
	
	const int w = hf.width;
	const int h = hf.height;
	const int spanCount = rcGetHeightFieldSpanCount(ctx, hf);

	// Fill in header.
	chf.width = w;
	chf.height = h;
	chf.spanCount = spanCount;
	chf.walkableHeight = walkableHeight;
	chf.walkableClimb = walkableClimb;
	chf.maxRegions = 0;
	rcVcopy(chf.bmin, hf.bmin);
	rcVcopy(chf.bmax, hf.bmax);
	chf.bmax[1] += walkableHeight*hf.ch;
	chf.cs = hf.cs;
	chf.ch = hf.ch;
	chf.cells = (rcCompactCell*)rcAlloc(sizeof(rcCompactCell)*w*h, RC_ALLOC_PERM);
	if (!chf.cells)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Out of memory 'chf.cells' (%d)", w*h);
		return false;
	}
	memset(chf.cells, 0, sizeof(rcCompactCell)*w*h);
	chf.spans = (rcCompactSpan*)rcAlloc(sizeof(rcCompactSpan)*spanCount, RC_ALLOC_PERM);
	if (!chf.spans)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Out of memory 'chf.spans' (%d)", spanCount);
		return false;
	}
	memset(chf.spans, 0, sizeof(rcCompactSpan)*spanCount);
	chf.areas = (unsigned char*)rcAlloc(sizeof(unsigned char)*spanCount, RC_ALLOC_PERM);
	if (!chf.areas)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Out of memory 'chf.areas' (%d)", spanCount);
		return false;
	}
	memset(chf.areas, RC_NULL_AREA, sizeof(unsigned char)*spanCount);
	
	const int MAX_HEIGHT = 0xffff;
	
	// Fill in cells and spans.
	int idx = 0;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const rcSpan* s = hf.spans[x + y*w];
			// If there are no spans at this cell, just leave the data to index=0, count=0.
			if (!s) continue;
			rcCompactCell& c = chf.cells[x+y*w];
			c.index = idx;
			c.count = 0;
			while (s)
			{
				if (s->area != RC_NULL_AREA)
				{
					const int bot = (int)s->smax;
					const int top = s->next ? (int)s->next->smin : MAX_HEIGHT;
					chf.spans[idx].y = (unsigned short)rcClamp(bot, 0, 0xffff);
					chf.spans[idx].h = (unsigned char)rcClamp(top - bot, 0, 0xff);
					chf.areas[idx] = s->area;
					idx++;
					c.count++;
				}
				s = s->next;
			}
		}
	}

	// Find neighbour connections.
	const int MAX_LAYERS = RC_NOT_CONNECTED-1;
	int tooHighNeighbour = 0;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const rcCompactCell& c = chf.cells[x+y*w];
			for (int i = (int)c.index, ni = (int)(c.index+c.count); i < ni; ++i)
			{
				rcCompactSpan& s = chf.spans[i];
				
				for (int dir = 0; dir < 4; ++dir)
				{
					rcSetCon(s, dir, RC_NOT_CONNECTED);
					const int nx = x + rcGetDirOffsetX(dir);
					const int ny = y + rcGetDirOffsetY(dir);
					// First check that the neighbour cell is in bounds.
					if (nx < 0 || ny < 0 || nx >= w || ny >= h)
						continue;
						
					// Iterate over all neighbour spans and check if any of the is
					// accessible from current cell.
					const rcCompactCell& nc = chf.cells[nx+ny*w];
					for (int k = (int)nc.index, nk = (int)(nc.index+nc.count); k < nk; ++k)
					{
						const rcCompactSpan& ns = chf.spans[k];
						const int bot = rcMax(s.y, ns.y);
						const int top = rcMin(s.y+s.h, ns.y+ns.h);

						// Check that the gap between the spans is walkable,
						// and that the climb height between the gaps is not too high.
						if ((top - bot) >= walkableHeight && rcAbs((int)ns.y - (int)s.y) <= walkableClimb)
						{
							// Mark direction as walkable.
							const int idx = k - (int)nc.index;
							if (idx < 0 || idx > MAX_LAYERS)
							{
								tooHighNeighbour = rcMax(tooHighNeighbour, idx);
								continue;
							}
							rcSetCon(s, dir, idx);
							break;
						}
					}
					
				}
			}
		}
	}
	
	if (tooHighNeighbour > MAX_LAYERS)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Heightfield has too many layers %d (max: %d)",
				 tooHighNeighbour, MAX_LAYERS);
	}
		
	ctx->stopTimer(RC_TIMER_BUILD_COMPACTHEIGHTFIELD);
	
	return true;
}


rcLeanHeightfield* rcBuildLeanHeightfield(rcContext* ctx, rcHeightfield& hf, const int walkableHeight)
{
	rcAssert(ctx);
	
	ctx->startTimer(RC_TIMER_BUILD_LEANHEIGHTFIELD);
	
	const int w = hf.width;
	const int h = hf.height;
	const int spanCount = rcGetHeightFieldSpanCount(ctx, hf);
	
	const int headerSize = rcAlign4(sizeof(rcLeanHeightfield));
	const int countsSize = rcAlign4(sizeof(unsigned char)*w*h);
	const int floorsSize = rcAlign4(sizeof(unsigned short)*spanCount);
	const int areasSize = rcAlign4(sizeof(unsigned char)*spanCount);
	const int dataSize = headerSize + countsSize + floorsSize + areasSize;
	
	unsigned char* data = (unsigned char*)rcAlloc(dataSize, RC_ALLOC_PERM);
	if (!data)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildLeanHeightfield: Out of memory (%d)", dataSize);
		return 0;
	}
	
	rcLeanHeightfield* lhf = (rcLeanHeightfield*)&data[0];
	unsigned char* counts = (unsigned char*)&data[headerSize];
	unsigned short* floors = (unsigned short*)&data[headerSize+countsSize];
	unsigned char* areas = (unsigned char*)&data[headerSize+countsSize+floorsSize];
	
	// Fill in header.
	lhf->width = w;
	lhf->height = h;
	lhf->spanCount = spanCount;
	rcVcopy(lhf->bmin, hf.bmin);
	rcVcopy(lhf->bmax, hf.bmax);
	lhf->cs = hf.cs;
	lhf->ch = hf.ch;
	lhf->size = dataSize;
	
	memset(counts, 0, w*h);
	memset(floors, 0, sizeof(unsigned short)*spanCount);
	memset(areas, RC_NULL_AREA, sizeof(unsigned char)*spanCount);
	
	const int MAX_HEIGHT = 0xffff;
	const int MAX_Y = (1<<RC_SPAN_HEIGHT_BITS)-1;
	const int MAX_H = (1<<(16-RC_SPAN_HEIGHT_BITS))-1;
	
	// Fill in cells and spans.
	int idx = 0;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const rcSpan* s = hf.spans[x+y*w];
			
			unsigned char& count = counts[x+y*w];
			count = 0;
			
			while (s)
			{
				if (s->area != RC_NULL_AREA)
				{
					const int bot = (int)s->smax;
					const int top = s->next ? (int)s->next->smin : MAX_HEIGHT;
					const int space = top - bot;
					unsigned short y = (unsigned short)rcClamp(bot, 0, MAX_Y);
					// TODO: Make sure 'h' can encode at least walkableClimb worth of values. 
					unsigned short h = 0; // Height stores the space above the walkable height.
					if (space >= walkableHeight)
						h = (unsigned short)rcClamp(1+(space - walkableHeight)/2, 0, MAX_H);
					
					floors[idx] = y | (h << RC_SPAN_HEIGHT_BITS);
					areas[idx] = s->area;
					idx++;
					count++;
				}
				s = s->next;
			}
		}
	}
	
	ctx->stopTimer(RC_TIMER_BUILD_LEANHEIGHTFIELD);
	
	return lhf;
}

bool rcBuildCompactHeightfield(rcContext* ctx, const int walkableHeight, const int walkableClimb,
							   rcLeanHeightfield& lhf, rcCompactHeightfield& chf)
{
	rcAssert(ctx);
	
	ctx->startTimer(RC_TIMER_BUILD_COMPACTHEIGHTFIELD);
	
	const int w = lhf.width;
	const int h = lhf.height;
	const int spanCount = lhf.spanCount;
	
	// Fill in header.
	chf.width = w;
	chf.height = h;
	chf.spanCount = spanCount;
	chf.walkableHeight = walkableHeight;
	chf.walkableClimb = walkableClimb;
	chf.maxRegions = 0;
	rcVcopy(chf.bmin, lhf.bmin);
	rcVcopy(chf.bmax, lhf.bmax);
	chf.bmax[1] += walkableHeight*lhf.ch;
	chf.cs = lhf.cs;
	chf.ch = lhf.ch;
	chf.cells = (rcCompactCell*)rcAlloc(sizeof(rcCompactCell)*w*h, RC_ALLOC_PERM);
	if (!chf.cells)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Out of memory 'chf.cells' (%d)", w*h);
		return false;
	}
	memset(chf.cells, 0, sizeof(rcCompactCell)*w*h);
	chf.spans = (rcCompactSpan*)rcAlloc(sizeof(rcCompactSpan)*spanCount, RC_ALLOC_PERM);
	if (!chf.spans)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Out of memory 'chf.spans' (%d)", spanCount);
		return false;
	}
	memset(chf.spans, 0, sizeof(rcCompactSpan)*spanCount);
	chf.areas = (unsigned char*)rcAlloc(sizeof(unsigned char)*spanCount, RC_ALLOC_PERM);
	if (!chf.areas)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Out of memory 'chf.areas' (%d)", spanCount);
		return false;
	}
	memset(chf.areas, RC_NULL_AREA, sizeof(unsigned char)*spanCount);
	
	const int headerSize = rcAlign4(sizeof(rcLeanHeightfield));
	const int countsSize = rcAlign4(sizeof(unsigned char)*lhf.width*lhf.height);
	const int floorsSize = rcAlign4(sizeof(unsigned short)*lhf.spanCount);
	const unsigned char* data = (const unsigned char*)&lhf;
	const unsigned char* counts = (const unsigned char*)&data[headerSize];
	const unsigned short* floors = (const unsigned short*)&data[headerSize+countsSize];
	const unsigned char* areas = (const unsigned char*)&data[headerSize+countsSize+floorsSize];
	
	const unsigned short MASK_Y = (1<<RC_SPAN_HEIGHT_BITS)-1;
	const unsigned short MASK_H = (1<<(16-RC_SPAN_HEIGHT_BITS))-1;
	
	// Fill in cells and spans.
	int idx = 0;
	for (int y = 0; y < chf.height; ++y)
	{
		for (int x = 0; x < chf.width; ++x)
		{
			const int count = counts[x+y*chf.width];
			
			rcCompactCell& c = chf.cells[x+y*w];
			c.index = idx;
			c.count = count;
			
			for (int i = idx, ni = idx+count; i < ni; ++i)
			{
				unsigned short y = (unsigned short)(floors[i] & MASK_Y);
				unsigned char h = (unsigned char)((floors[i]>>RC_SPAN_HEIGHT_BITS) & MASK_H);
				chf.spans[i].y = y;
				chf.spans[i].h = h == 0 ? 0 : (unsigned char)(walkableHeight + (h-1)*2);
				chf.areas[i] = areas[i];
			}
			
			idx += count;
		}
	}
	
	// Find neighbour connections.
	const int MAX_LAYERS = RC_NOT_CONNECTED-1;
	int tooHighNeighbour = 0;
	
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const rcCompactCell& c = chf.cells[x+y*w];
			for (int i = (int)c.index, ni = (int)(c.index+c.count); i < ni; ++i)
			{
				rcCompactSpan& s = chf.spans[i];
				
				for (int dir = 0; dir < 4; ++dir)
				{
					rcSetCon(s, dir, RC_NOT_CONNECTED);
					const int nx = x + rcGetDirOffsetX(dir);
					const int ny = y + rcGetDirOffsetY(dir);
					// First check that the neighbour cell is in bounds.
					if (nx < 0 || ny < 0 || nx >= w || ny >= h)
						continue;
					
					// Iterate over all neighbour spans and check if any of the is
					// accessible from current cell.
					const rcCompactCell& nc = chf.cells[nx+ny*w];
					for (int k = (int)nc.index, nk = (int)(nc.index+nc.count); k < nk; ++k)
					{
						const rcCompactSpan& ns = chf.spans[k];
						const int bot = rcMax(s.y, ns.y);
						const int top = rcMin(s.y+s.h, ns.y+ns.h);
						
						// Check that the gap between the spans is walkable,
						// and that the climb height between the gaps is not too high.
						if ((top - bot) >= walkableHeight && rcAbs((int)ns.y - (int)s.y) <= walkableClimb)
						{
							// Mark direction as walkable.
							const int idx = k - (int)nc.index;
							if (idx < 0 || idx > MAX_LAYERS)
							{
								tooHighNeighbour = rcMax(tooHighNeighbour, idx);
								continue;
							}
							rcSetCon(s, dir, idx);
							break;
						}
					}
					
				}
			}
		}
	}
	
	if (tooHighNeighbour > MAX_LAYERS)
	{
		ctx->log(RC_LOG_ERROR, "rcBuildCompactHeightfield: Heightfield has too many layers %d (max: %d)",
				 tooHighNeighbour, MAX_LAYERS);
	}
	
	ctx->stopTimer(RC_TIMER_BUILD_COMPACTHEIGHTFIELD);
	
	return true;
}


/*
static int getHeightfieldMemoryUsage(const rcHeightfield& hf)
{
	int size = 0;
	size += sizeof(hf);
	size += hf.width * hf.height * sizeof(rcSpan*);
	
	rcSpanPool* pool = hf.pools;
	while (pool)
	{
		size += (sizeof(rcSpanPool) - sizeof(rcSpan)) + sizeof(rcSpan)*RC_SPANS_PER_POOL;
		pool = pool->next;
	}
	return size;
}

static int getCompactHeightFieldMemoryusage(const rcCompactHeightfield& chf)
{
	int size = 0;
	size += sizeof(rcCompactHeightfield);
	size += sizeof(rcCompactSpan) * chf.spanCount;
	size += sizeof(rcCompactCell) * chf.width * chf.height;
	return size;
}
*/