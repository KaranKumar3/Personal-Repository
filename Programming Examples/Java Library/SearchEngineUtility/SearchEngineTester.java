import static org.junit.Assert.assertEquals;

import org.junit.Test;

/**
 * Unit test harness.  Uses Junit 4 library.
 */
public class SearchEngineTester {
	
	private static final int[] TEST_ARRAY_NON_UNIFORM = {1,1,2,2,3,4,5,50,100,1000,1000};
	private static final int[] TEST_ARRAY_UNIFORM = {1,2,3,4,5,6,7,8,9,10};

	/*
	 * Tests for interpolation search.
	 */
	@Test
	public void testInterpolationSearchIterative0() {
		
		int result = SearchEngineUtility.interpolationSearchIterative(TEST_ARRAY_NON_UNIFORM, 100);
		int expected = 8;
		
		assertEquals(expected, result);
			
	}
	
	
	/**
	 * Test lower bound.
	 */
	@Test
	public void testInterpolationSearchIterative1() {
		
		int result = SearchEngineUtility.interpolationSearchIterative(TEST_ARRAY_NON_UNIFORM, 1);
		int expected = 0;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test upper bound.
	 */
	@Test
	public void testInterpolationSearchIterative2() {
		
		int result = SearchEngineUtility.interpolationSearchIterative(TEST_ARRAY_NON_UNIFORM, 1000);
		int expected = 10;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test mid range value.
	 */
	@Test
	public void testInterpolationSearchIterative3() {
		
		int result = SearchEngineUtility.interpolationSearchIterative(TEST_ARRAY_NON_UNIFORM, 5);
		int expected = 6;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test value not in array < min array value.
	 */
	@Test
	public void testInterpolationSearchIterative4() {
		
		int result = SearchEngineUtility.interpolationSearchIterative(TEST_ARRAY_NON_UNIFORM, 0);
		int expected = -1;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test value not in array > max array value.
	 */
	@Test
	public void testInterpolationSearchIterative5() {
		
		int result = SearchEngineUtility.interpolationSearchIterative(TEST_ARRAY_NON_UNIFORM, 1001);
		int expected = -1;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test value not in array where target > min and < max.
	 */
	@Test
	public void testInterpolationSearchIterative6() {
		
		int result = SearchEngineUtility.interpolationSearchIterative(TEST_ARRAY_NON_UNIFORM, 6);
		int expected = -1;
		
		assertEquals(expected, result);
			
	}
	
	/*
	 * Tests for recursive search.
	 */
	
	/**
	 * Test lower bound.
	 */
	@Test
	public void testInterpolationSearchRecursive1() {
		
		int result = SearchEngineUtility.interpolationSearchRecursive(TEST_ARRAY_NON_UNIFORM, 1);
		int expected = 0;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test upper bound.
	 */
	@Test
	public void testInterpolationSearchRecursive2() {
		
		int result = SearchEngineUtility.interpolationSearchRecursive(TEST_ARRAY_NON_UNIFORM, 1000);
		int expected = 10;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test mid range value.
	 */
	@Test
	public void testInterpolationSearchRecursive3() {
		
		int result = SearchEngineUtility.interpolationSearchRecursive(TEST_ARRAY_NON_UNIFORM, 5);
		int expected = 6;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test value not in array < min array value.
	 */
	@Test
	public void testInterpolationSearchRecursive4() {
		
		int result = SearchEngineUtility.interpolationSearchRecursive(TEST_ARRAY_NON_UNIFORM, 0);
		int expected = -1;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test value not in array > max array value.
	 */
	@Test
	public void testInterpolationSearchRecursive5() {
		
		int result = SearchEngineUtility.interpolationSearchRecursive(TEST_ARRAY_NON_UNIFORM, 1001);
		int expected = -1;
		
		assertEquals(expected, result);
			
	}
	
	/**
	 * Test value not in array where target > min and < max.
	 */
	@Test
	public void testInterpolationSearchRecursive6() {
		
		int result = SearchEngineUtility.interpolationSearchRecursive(TEST_ARRAY_NON_UNIFORM, 6);
		int expected = -1;
		
		assertEquals(expected, result);
			
	}

}
