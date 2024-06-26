#pragma once

#include "Phoenix/Common.hpp"
#include "Phoenix/Log.hpp"
#include "Phoenix/Mesh.hpp"
#include "Phoenix/gfx/Api.hpp"
#include "assimp/TinyFormatter.h"
#include "assimp/mesh.h"
#include "assimp/vector2.h"
#include "assimp/vector3.h"
#include "fmt/core.h"
#include "glm/fwd.hpp"
#include <Phoenix/MeshImporter.hpp>

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Logger.hpp>
#include <assimp/DefaultLogger.hpp>
#include <cstdint>
#include <cstdio>
#include <vector>
namespace phnx {
    Ref<Mesh> ImportFBX(const std::string &path) {

        Assimp::Logger::LogSeverity severity = Assimp::Logger::DEBUGGING;

	    // Create a logger instance for Console Output
	    Assimp::DefaultLogger::create("",severity, aiDefaultLogStream_STDOUT);

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
        aiProcess_JoinIdenticalVertices |
        aiProcess_ForceGenNormals    | 
        aiProcess_FixInfacingNormals |
        aiProcess_Triangulate);

        if (!scene) {
            PHNX_ERR("Failed To Import Model '%s'", path.c_str());
            return nullptr;
        }

        aiMesh* root_mesh = scene->mMeshes[0];

        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
        


        for (int i = 0; i < root_mesh->mNumVertices; i++) {

            Vertex vtx{};

            aiVector3D vert = root_mesh->mVertices[i];
            vtx.Position = {vert.x, vert.y, vert.z};
            
            if (root_mesh->HasTextureCoords(0)) {
                vtx.TexCoord.x = root_mesh->mTextureCoords[0][i].x;
                vtx.TexCoord.y = root_mesh->mTextureCoords[0][i].y;
            };


            if (root_mesh->HasNormals()) {
            aiVector3f normal = root_mesh->mNormals[i];

                vtx.Normal = {
                    normal.x, normal.y, normal.z
                };
            }

            printf("Pos[%d]: (%0.2f, %0.2f, %02.f)\n", i, vtx.Position.x, vtx.Position.y, vtx.Position.z);

            vertices.emplace_back(vtx);
        }

        for (int i = 0; i < root_mesh->mNumFaces; i++) {
            aiFace face = root_mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++) {
                printf("Index: %d\n", face.mIndices[j]);
                indices.push_back(face.mIndices[j] & 0xFFFF);
            }
        }

        Ref<Mesh> mesh = MakeRef<Mesh>();
        mesh->SetTriangles(indices);
        mesh->SetVertices(vertices);

        return mesh;

    }
}