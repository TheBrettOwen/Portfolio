package project2;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
* JUnit Test class for RatingSummary
  @author Owen
  @author McPherson
*/
class RatingSummaryTest {

	public RatingSummary rs;
	
	@BeforeEach
	public void setup() {
		rs = new RatingSummary("A1EE2E3N7PW666", 2);
	}

	/**
	* Test Constructor(String, long, Float, Float, Float, Float)
	*/
	@Test
	void testRatingSummaryStringLongListOfFloat() {
		String actualOutput = "A1EE2E3N7PW666,2,2.0,2.0,2.0,2.0\n";
		rs.setList(2, 2, 2, 2);
		assertTrue(actualOutput.equals(rs.toString()));
	}

	/**
	* Test Example
	*/
	@Test
	void testEquals() {
		RatingSummary rs2;
		rs2 = rs;
		assertEquals(rs2, rs);
	}

	/**
	* Test setList()
	*/
	@Test
	void testSetList(){
		rs.setList();
		assertNotNull(rs.getList(), "testSetList Failed");
		
	}
	
	/**
	* Test setList(float, float, float, float)
	*/
	@Test
	void testSetListFloat4() {
		rs.setList(2,2,2,2);
		List<Float> testList = new ArrayList<>();
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		List<Float> result = rs.getList();
		
		assertEquals(result, testList);
	}

	/**
	* Test setList()
	*/
	@Test
	void testSetListReturnsList() {
		rs.setList(); 
		List<Float> result = new ArrayList<>(); 
		result = rs.getList(); 
		assertNotNull(result);
	}

	/**
	* Test getList()
	*/
	@Test
	void testGetList() {
		rs.setList(2,2,2,2);
		List<Float> testList = new ArrayList<>();
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		List<Float> result = rs.getList();
		
		assertEquals(result, testList);
	}

	/**
	* Test createList()
	*/
	@Test
	void testCreateList(){
		List<Float> result = rs.createList();
		assertNotNull(result);
	}

	/**
	* Test createList(Float, Float, Float, Float)
	*/
	@Test
	void testCreateListFloat4(){
		List<Float> result = rs1.createList( 2, 2, 2, 2);
	  	List<Float> testList = new ArrayList<>();
	 	testList.add(2f);
	  	testList.add(2f);
	  	testList.add(2f);
		testList.add(2f);
		  
		assertEquals(result, testList);
	}

	/**
	* Test toString()
	*/
	@Test
	void testToString(){
		rs.setList(2, 2, 2, 2);
		String result = rs.toString();
		assertEquals(result, "A1EE2E3N7PW666,2,2,2,2\n");
	}

	/**
	* Test avgScore()
	*/
	@Test
	void testAvgScores(){
		rs.setList(2, 2, 2, 2);
		Float result = rs.avgScore();

		assertEquals(result, 0);
		
		rs.setList(5, 6, 2, 2);
		result = rs.avgScore();

		assertEquals(result, 3);

		rs.setList(5, 6, 2, 2);
		result = rs.avgScore();

		assertEquals(result, 3);
	}

	/**
	* Test stDevScore()
	*/
	@Test
	void testStDevScores(){
		rs.setList(2, 2, 2, 2);
		Float result = rs.stDevScore();

		assertEquals(result, 0);
		
		rs.setList(5, 6, 2, 2);
		result = rs.stDevScore();

		assertEquals(result, 4);

		rs.setList(5, 6, 2, 2);
		result = rs.stDevScore();

		assertEquals(result, 4);
	}
	
	/**
	* Test CompareTo()
	*/
	@Test
	void testSetDegreeLong() {
		rs.setDegree(3);
		assertEquals(3,rs.getDegree());
	}

	/**
	* Test CompareTo()
	*/
	@Test
	void testSetDegreeList() {
		List<Rating> testList = new ArrayList<>(); 
		testList.add(new Rating("A1EE2E3N7PW666", "testString", 5));
		testList.add(new Rating("testString", "A1EE2E3N7PW666", 5));
		testList.add(new Rating("testString", "testString", 5));
		rs = new RatingSummary("A1EE2E3N7PW666", 0);
		rs.setDegree(testList); 
		Long result = rs.getDegree(); 
		assertEquals(result, 2); 
	}

	/**
	* Test CompareTo()
	*/
	@Test
	void testGetDegreeLong() {
		rs.setDegree(3);
		assertEquals(3,rs.getDegree());
	}

	//tests NodeID getter
	@Test
	void testGetNodeID(){
		String result = rs.getNodeID();
		assertEquals(result, "A1EE2E3N7PW666");
	}

	//Tests if the getter for both NodeID and inDegree
	@Test
	void testRatingSummaryStringLong(){
		String resultString = rs.getNodeID();
		Long resultLong = rs.getDegree();
		assertEquals(resultString, "A1EE2E3N7PW666");
		assertEquals(resultLong, 2);
	}

	//tests the NodeID, Degree, and List at the same time by passing a list of floats
	@Test
	void testRatingSummaryStringLongList() {
		List<Float> testList = new ArrayList<>();
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, testList);
		String resultString = rs1.getNodeID();
		Long resultLong = rs1.getDegree();
		List<Float> result = rs1.getList();
		
		assertEquals(resultString, "A1EE2E3N7PW666");
		assertEquals(resultLong, 2);
		assertEquals(result, testList);
	}

	/**
	* Test Constructor(String, long, Float, Float, Float, Float)
	*/
	@Test
	void testRatingSummaryStringLongFloat4() {
		List<Float> testList = new ArrayList<>();
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		testList.add(2f);
		RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 2, 2);
		String resultString = rs1.getNodeID();
		Long resultLong = rs1.getDegree();
		List<Float> result = rs1.getList();
		
		assertEquals(resultString, "A1EE2E3N7PW666");
		assertEquals(resultLong, 2);
		assertEquals(result, testList);
	}

	/**
	* Test equals()
	*/
	@Test
	void testAbstractEquals() {
		RatingSummary rs2;
		rs2 = rs;
		bool result = rs.equals(rs2); 
		assertTrue(result);
	}

	/**
	* Test compareTo()
	*/
	@Test
	void testCompareTo() {
		RatingSummary rs2;
		rs2 = rs1;
		int result = rs1.compareTo(rs2); 
		assertEquals(result, 0);

		result = rs.compareTo(rs2);

		assertEquals(result, rs.ss().compareTo(rs2.sortStats()));
	}

	

}
