/*=============================================================================
 * Partition class for CloudCompare (Ioannis Farmakis, 2026)
 *
 * Provides point cloud partitioning/segmentation based on the Parallel Cut
 * Pursuit algorithm, built on top of the Graph and CP classes of this
 * library.
 *
 * Reference:
 * Hugo Raguet and Loic Landrieu, 2019, "Parallel Cut Pursuit for
 * Minimization of the Graph Total Variation"
 * (https://doi.org/10.48550/arXiv.1905.02316).
 *===========================================================================*/
#pragma once

// system
#include <cstdint>
#include <vector>

// Local
#include <Graph.h>

namespace PCP
{
	//! Parameters and input features of the Parallel Cut Pursuit algorithm
	struct Parameters
	{
		int32_t knn            = 0;    //!< maximum number of neighbors to search for each point (k)
		double  knnRadius      = 0.0;  //!< maximum distance to search for neighbors
		int32_t D              = 0;    //!< number of dimensions of the feature space
		float   regularization = 0.0f; //!< regularization strength
		float   spatialWeight  = 0.0f; //!< weight of spatial coordinates in the feature space
		int32_t cutoff         = 0;    //!< minimum component weight

		std::vector<float> Y; //!< feature matrix (size = number of points * D, row-major)
	};

	//! Point cloud partitioning algorithms based on the Parallel Cut Pursuit method
	class Partition
	{
	  public:
		//! Partitions a point cloud using the Parallel Cut Pursuit algorithm
		/** The algorithm is described in Hugo Raguet and Loic Landrieu, 2019 paper
		    titled "Parallel Cut Pursuit for Minimization of the Graph Total
		Variation" (https://doi.org/10.48550/arXiv.1905.02316). \param theCloud the
		point cloud to label
		\param params the algorithm parameters and features;
		params.components receives the output
		  \param knn the maximum number of neighbors to search for each point (k)
		  \param knnRadius the maximum distance to search for neighbors
		  \param N the number of points in the cloud
		  \param D the number of dimensions for the feature space
		  \param Y the feature matrix (size N * D, row-major)
		  \param regularization the regularization parameter for cut pursuit
		  \param spatialWeight the weight for spatial coordinates in the feature space
		  \param cutoff the minimum component weight for the cut pursuit algorithm
		\param components array to store the output (size should be equal to the
		number of points in the cloud) \param progressCb process progress through this
		callback mechanism \param theOctree the cloud octree if it has already been
		computed \return the number of components (>= 0) or an error code (< 0)
		**/
		static int LabelCutPursuitComponents(
		    CCCoreLib::GenericIndexedCloudPersist* theCloud,
		    const Parameters&                      params,
		    std::vector<int32_t>&                  components,
		    CCCoreLib::GenericProgressCallback*    progressCb = nullptr,
		    CCCoreLib::DgmOctree*                  theOctree  = nullptr);
	};
} // namespace PCP
