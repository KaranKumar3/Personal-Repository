public class SearchEngineUtility {

	/**
	 * Searches the specified array of objects using a linear search algorithm.
	 *
	 * @param data
	 *            the array to be searched
	 * @param min
	 *            the integer representation of the minimum value
	 * @param max
	 *            the integer representation of the maximum value
	 * @param target
	 *            the element being searched for
	 * @return int representing the target value index in the array. Returns -1
	 *         if not found.
	 */
	public <T> int linearSearch(T[] data, int min, int max, T target) {

		int index = min;
		int targetIndex = -1;
		boolean found = false;

		while (!found && index <= max) {

			found = data[index].equals(target);

			if (found) {
				targetIndex = index;
			}

			index++;

		}

		return targetIndex;

	}

	/**
	 * Searches the specified array of objects using a binary search algorithm.
	 * 
	 * @param data
	 *            the array to be searched
	 * @param min
	 *            the integer representation of the minimum value
	 * @param max
	 *            the integer representation of the maximum value
	 * @param target
	 *            the element being searched for
	 * @return int representing the target value index in the array. Returns -1
	 *         if not found.
	 */
	public static <T extends Comparable<T>> int binarySearch(T[] data, int min, int max, T target) {

		int index = -1;

		int midpoint = (min + max) / 2; // determine the midpoint

		if (data[midpoint].compareTo(target) == 0) {

			index = midpoint;

		} else if (data[midpoint].compareTo(target) > 0) {

			if (min <= midpoint - 1) {

				index = binarySearch(data, min, midpoint - 1, target);

			}

		} else if (midpoint + 1 <= max) {

			index = binarySearch(data, midpoint + 1, max, target);

		}

		return index;

	}

	/**
	 * Iterative implementation of a linear interpolation search.
	 * 
	 * @param sortedArray
	 *            the array to be searched
	 * @param targetValue
	 *            the value being searched for
	 * @return int index of targetValue. Returns -1 if value not found.
	 */
	public static int interpolationSearchIterative(int[] sortedArray, int targetValue) {

		int min = 0;
		int max = sortedArray.length - 1;
		int mid;
		final int NOT_FOUND = -1;

		// Corner case where array is all same values
		if (sortedArray[max] - sortedArray[min] == 0)
			return (min + max) / 2;

		/*
		 * While our target value is between the array[min] and array[max]
		 * values.
		 */
		while (sortedArray[min] <= targetValue && sortedArray[max] >= targetValue) {

			// Out of range is possible
			mid = min + ((targetValue - sortedArray[min]) * (max - min)) / (sortedArray[max] - sortedArray[min]);

			if (sortedArray[mid] < targetValue) {

				// Target value is greater than mid value
				min = mid + 1;

			} else if (sortedArray[mid] > targetValue) {

				// Target value is less than mid value
				max = mid - 1;

			} else {

				// Found value
				return mid;

			}
		}

		/*
		 * Corner case where our target is equal to min value after search has
		 * completed.
		 */
		if (sortedArray[min] == targetValue) {

			return min;

		} else {

			// Value not found
			return NOT_FOUND;

		}
	}

	/**
	 * Recursive implementation of a linear interpolation search.
	 * 
	 * @param sortedArray
	 *            the array to be searched
	 * @param min
	 *            the int index of the minimum value to search
	 * @param max
	 *            the int index of the maximum value to search
	 * @param targetValue
	 *            the value being searched for
	 * @return int index of targetValue. Returns -1 if value not found.
	 */
	public static int interpolationSearchRecursive(int[] sortedArray, int min, int max, int targetValue) {

		int mid;
		int foundIndex = -1;
		final int NOT_FOUND = -1;

		/*
		 * Base Case: Case where sub-array is all same values.
		 */
		if (sortedArray[max] - sortedArray[min] == 0) {

			return (min + max) / 2;

		}

		/*
		 * Base Case: Our target value is no longer between our min and max
		 * indexes. Basically we have data in this case that 'broke' our
		 * algorithm.
		 */
		if (sortedArray[min] > targetValue || sortedArray[max] < targetValue) {

			return NOT_FOUND;

		}

		// Out of range is possible...
		mid = min + ((targetValue - sortedArray[min]) * (max - min)) / (sortedArray[max] - sortedArray[min]);

		/*
		 * if-statement used to eliminate ArrayIndexOutOfBoundException under
		 * certain circumstances.
		 */
		if ((mid <= sortedArray.length - 1) && (mid >= 0)) {

			if (sortedArray[mid] < targetValue) {

				// Target value is greater than mid value
				foundIndex = interpolationSearchRecursive(sortedArray, mid + 1, max, targetValue);

			} else if (sortedArray[mid] > targetValue) {

				// Target value is less than mid value
				foundIndex = interpolationSearchRecursive(sortedArray, min, mid - 1, targetValue);

			} else {

				/*
				 * Base Case: Found target value
				 */
				return mid;

			}

		}

		/*
		 * Base Case: Our target value has fallen out of the range of our min
		 * and max indexes for our array. Will return -1 in this case.
		 */
		return foundIndex;

	}

	/**
	 * Recursive implementation of a linear interpolation search.
	 * 
	 * @param sortedArray
	 *            the array to be searched
	 * @param targetValue
	 *            the value being searched for
	 * @return int index of targetValue. Returns -1 if value not found.
	 */
	public static int interpolationSearchRecursive(int[] sortedArray, int targetValue) {

		return interpolationSearchRecursive(sortedArray, 0, sortedArray.length - 1, targetValue);

	}

}
