package project2;

import org.junit.jupiter.api.Test;
import static org.hamcrest.MatcherAssert.assertThat; 
import static org.hamcrest.Matchers.*;

import java.util.ArrayList;
import java.util.List;

/**
* Hamcrest Test class for RatingSummary
  @author Owen
  @author McPherson
*/
public class RatingSummaryHamcrestTest {
	/**
	* Test Example
	*/
  @Test 
  public void testEquals() { 
  	RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	RatingSummary rs2 = rs1;
	
    assertThat(rs1, equalTo(rs2)); 

  } 
  /**
	* Test equals()
	*/
  @Test
  public void testAbstractEquals() {
	RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	RatingSummary rs2 = rs1;
	boolean result = rs1.equals(rs2);
	
	assertThat(true, equalto(result));
  }
  /**
	* Test compareTo()
	*/
  @Test
  public void testCompareTo() {
	RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 2, 2);
	RatingSummary rs2 = rs1;
	int result = rs1.compareTo(rs2);
			
	asserThat(result, is(0));
	
	rs2 = new RatingSummary("A1EE2E3N7PW665", 3, 3, 3, 3, 3);
	result = rs1.compareTo(rs2);
	
	assertThat(result, is(rs1.sortStats().compareTo(rs2.sortStats())));
  }
  /**
	* Test setList(Float, Float, Float, Float)
	*/
  @Test 
  public void testSetListFloatFloatFloatFloat() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  rs1.setList(2,2,2,2);
	  List<Float> testList = new ArrayList<>();
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  List<Float> result = rs1.getList();
	  
	  assertThat(result, equalto(testList));  
  }
  /**
	* Test setList()
	*/
  @Test 
  public void testSetList() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  rs1.setList();
	  List<Float> result = rs1.getList();
	  
	  assertThat(result, notNullValue());
  }
  /**
	* Test getList()
	*/
  @Test 
  public void testGetList() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  rs1.setList(2,2,2,2);
	  List<Float> testList = new ArrayList<>();
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  List<Float> result = rs1.getList();
	  
	  assertThat(result, equalto(testList));  
  }
  /**
	* Test setDegree(long)
	*/
  @Test
  public void testSetDegreeLong() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  rs1.setDegree(3);
	  long result = rs1.getDegree();
	  
	  assertThat(result, is(3));
	  
  }
  /**
	* Test CompareTo()
	*/
  @Test
  public void testGetDegree() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  rs1.setDegree(3);
	  long result = rs1.getDegree();
	  
	  assertThat(result, is(3));
	  
  }
  /**
	* Test CompareTo()
	*/
  @Test
  public void testSetDegreeList() {
	  List<Rating> testList = new ArrayList<>();
	  testList.add(new Rating("A1EE2E3N7PW666", "testString", 5));
	  testList.add(new Rating("testString", "A1EE2E3N7PW666", 5));
	  testList.add(new Rating("testString", "testString", 5));
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 0);
	  rs1.setDegree(testList);
	  long result = rs1.getDegree();
	  
	  assertThat(result, is(2));
  }
  /**
	* Test CompareTo()
	*/
  @Test
  public void testGetNodeID() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  String result = rs1.getNodeID();
	  
	  assertThat(result, is("A1EE2E3N7PW666"));
  }
  /**
	* Test CompareTo()
	*/
  @Test
  public void testRatingSummaryStringLong() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  String resultString = rs1.getNodeID();
	  long resultLong = rs1.getDegree();
	  
	  assertThat(resultString, is("A1EE2E3N7PW666"));
	  assertThat(resultLong, is(2));
  }
  /**
	* Test CompareTo()
	*/
  @Test
  public void testRatingSummaryStringLongList() {
	  List<Float> testList = new ArrayList<>();
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, testList);
	  String resultString = rs1.getNodeID();
	  long resultLong = rs1.getDegree();
	  List<Float> resultList = rs1.getList();
	  
	  assertThat(resultString, is("A1EE2E3N7PW666"));
	  assertThat(resultLong, is(2));
	  assertThat(resultList, is(testList));
  }
  /**
	* Test Constructor(String, long, Float, Float, Float, Float)
	*/
  @Test
  public void testRatingSummaryStringLongFloatFloatFloatFloat() {
	  List<Float> testList = new ArrayList<>();
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 2, 2);
	  String resultString = rs1.getNodeID();
	  long resultLong = rs1.getDegree();
	  List<Float> resultList = rs1.getList();
	  
	  assertThat(resultString, is("A1EE2E3N7PW666"));
	  assertThat(resultLong, is(2));
	  assertThat(resultList, is(testList));
  }
  /**
	* Test Constructor(String, List) Not Implemented!
	*/
  @Test
  public void testRatingSummaryStringList() {
	    
  }
  /**
	* Test createList()
	*/
  @Test
  public void testCreateList() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  List<Float> result = rs1.createList();
	  
	  assertThat(result, isNotNull());
  }
  /**
	* Test createList(Float, Float, Float, Float)
	*/
  @Test
  public void testCreateListFloatFloatFloatFloat() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2);
	  List<Float> result = rs1.createList( 2, 2, 2, 2);
	  List<Float> testList = new ArrayList<>();
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  testList.add(2f);
	  
	  assertThat(result, is(testList));
  }
  /**
	* Test toString()
	*/
  @Test
  public void testToString() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 2, 2);
	  String result = rs1.toString();
	  
	  assertThat(result, is("A1EE2E3N7PW666,2,2,2,2\n"));
  }
  /**
	* Test collectStats() Not Implemented!
	*/
  @Test
  public void testCollectStats() {
	  
  }
  /**
	* Test collectProductStats() Not Implemented!
	*/
  @Test
  public void testCollectProductStats() {
	  
  }
  /**
	* Test collectReviewerStat() Not Implemented!
	*/
  @Test
  public void testCollectReviewerStat() {
	  
  }
  /**
	* Test avgScore()
	*/
  @Test
  public void testAvgScore() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 2, 2);
	  Float result = rs1.avgScore();
	  
	  assertThat(result, is(0));
	  
	  rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 5, 6, 2, 2);
	  result = rs1.avgScore();
	  
	  assertThat(result, is(3));
	  
	  rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 5, 6);
	  result = rs1.avgScore();
	  
	  assertThat(result, is(3));
  }
  /**
	* Test stDevScore()
	*/
  @Test
  public void testStDevScore() {
	  RatingSummary rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 2, 2);
	  Float result = rs1.stDevScore();
	  
	  assertThat(result, is(0));
	  
	  rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 5, 6, 2, 2);
	  result = rs1.stDevScore();
	  
	  assertThat(result, is(4));
	  
	  rs1 = new RatingSummary("A1EE2E3N7PW666", 2, 2, 2, 5, 6);
	  result = rs1.stDevScore();
	  
	  assertThat(result, is(4));
  } 
} 