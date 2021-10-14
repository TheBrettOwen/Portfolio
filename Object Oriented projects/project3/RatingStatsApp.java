package project3; 

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Set;
import java.util.HashSet;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.WindowConstants;

/**
 *  Provides functionality for interacting with the user, main class 
    @author tarek
	@author tesic
	@author Owen
	@author McPherson
 */
public class RatingStatsApp extends JFrame{

	private static final long serialVersionUID = 1L;
	static JFrame f;
	static JTextArea output, setupT;
	static JScrollPane scroll, scrollTwo; 
	static JTextField inputT;
	static JComboBox<String> dataDropdown; 
	static JButton display, add, exit, search, innerSearch, home, innerAdd, secInnerAdd;
	static String selection;

	static String[] dataArray; 
	static String newDataID="";
	static String rc, welcomeMessage;

	static boolean found = false; 

	static int stats;

	static DatasetHandler dh;
	static Set<String> datasets;

	static Dataset d;

	private RatingStatsApp(String title) {
		super(title); 
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		Component c = this; 
		JFrame f = this; 

		output=new JTextArea("Output");

		//dataDropdown=new JComboBox<>(dataArray);
		scroll = new JScrollPane(output);
		setupT=new JTextArea("Setup");
		scrollTwo = new JScrollPane(setupT);
		scrollTwo.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		inputT=new JTextField("Input");
		display=new JButton("Display Statistics");
		add=new JButton("Add Dataset");
		exit=new JButton("Exit");
		search=new JButton("Continue");
		home = new JButton("Home");
		innerAdd = new JButton("Continue");
		secInnerAdd = new JButton("Continue");
		innerSearch = new JButton("Compute");
		
		setupT.setBounds(10,10,560,300);
		setupT.setEditable(false);
		scrollTwo.setBounds(10,10,300,560);

		output.setBounds(10,320,560,260);
		output.setEditable(false);
		scroll.setBounds(10,320,560,260);

		inputT.setBounds(10,580,200,30);
		inputT.setVisible(false);

		//dataDropdown.setBounds(10,580,200,30);

		display.setBounds(10,620,150,40);
		add.setBounds(160,620,150,40);
		exit.setBounds(470,620,100,40);
		search.setBounds(10,620,100,40);
		search.setVisible(false);
		innerSearch.setBounds(10,620,100,40);
		innerSearch.setVisible(false);
		home.setBounds(110,620,100,40);
		home.setVisible(false);
		innerAdd.setBounds(10,620,100,40);
		innerAdd.setVisible(false);
		secInnerAdd.setBounds(10,620,100,40);
		secInnerAdd.setVisible(false);
		

		this.add(setupT);
		//this.add(dataDropdown);
		this.add(scroll);
		this.add(scrollTwo);
		this.add(display);
		this.add(add);
		this.add(exit);
		this.add(home);
		this.add(search);
		this.add(inputT);
		this.add(innerAdd);
		this.add(secInnerAdd);
		this.add(innerSearch);

		//this.setLayout(null);
		//this.setVisible(true);
		//this.setSize(700,700);
		//this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//this.setResizable(false);

		//selection = "";

		try{
			
			
			dh = new DatasetHandler();
			datasets = new HashSet<String>();

			for (Dataset temp : dh.getDataSets()){
				datasets.add(temp.toString());
			}

			int n = datasets.size();
			dataArray = new String[n];
			System.arraycopy(datasets.toArray(), 0, dataArray, 0, n); 

			dataDropdown=new JComboBox<>(dataArray);
			dataDropdown.setBounds(10,585,200,30);
			this.add(dataDropdown);

			this.setLayout(null);
			this.setVisible(true);
			this.setSize(590,700);
			this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			this.setResizable(false);

			selection = "";
			
			String setup = "Loading the datasets from:" + DataAnalysis.LINE_SEP
            	+ "     data folder: " + dh.getFolderPath() + DataAnalysis.LINE_SEP
				+ "     datasets available: " + dh.getDataSets() + DataAnalysis.LINE_SEP;
			setupT.setText("" + setup + " " + dh.printDB());
			
			welcomeMessage = "Choose one of the following functions:" + DataAnalysis.LINE_SEP
             + "\t Display computed statistics for specific dataID." + DataAnalysis.LINE_SEP
             + "\t Add new collection and compute statistics." + DataAnalysis.LINE_SEP
				+ "\t Exit program." + DataAnalysis.LINE_SEP;
			output.setText("" + welcomeMessage);

		}
		catch(IOException e){
			setupT.setText("Dataset path not found: " + e.getMessage());
			output.setText(" Please exit, check the file, and try again.");
		}
		display.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				newDataID = dataDropdown.getSelectedItem().toString();
				if (newDataID != "") {
					//this blocks processes computed statistics in dh
					int k = 20;
					//prints report to file and console 
					output.setText(dh.printReport(newDataID,k));
				}
				else {
					output.setText("No report printed yet, please add data.");
				}
			}
		});

		add.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				output.setText("Please enter new unique dataID: ");
				dataDropdown.setVisible(false);
				display.setVisible(false);
				add.setVisible(false);
				inputT.setVisible(true);
				innerAdd.setVisible(true);
				home.setVisible(true);
			}
			});
		exit.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				if(e.getSource()==exit){
					f.dispatchEvent(new WindowEvent(f, WindowEvent.WINDOW_CLOSING));
				}
			}
			});
		home.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				search.setVisible(false);
				inputT.setVisible(false);
				home.setVisible(false);
				innerAdd.setVisible(false);
				secInnerAdd.setVisible(false);
				innerSearch.setVisible(false);
				display.setVisible(true);
				add.setVisible(true);
				dataDropdown.setVisible(true);
	
				output.setText(welcomeMessage);
			}
			});
		search.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				search.setVisible(false);
				innerSearch.setVisible(true);
				newDataID = inputT.getText();

				if (!(dh.checkID(newDataID))){
					output.setText("dataID not in the current database, select another option");
				}else{
					found = true;
				}
				if (found){
					final String processStats = newDataID + ": statistics are already computed and saved \n"
						+ "Choose one of the following functions:\n\n"
						+ "\t 3. Use existing stat data.\n" 
						+ "\t 4. Process statistics again, I have new data.\n";
					
					try{
						d = dh.populateCollection(newDataID);
					}
					catch(IOException ee){
						output.setText("Dataset path not found: " + ee.getMessage() + " Please check the file and try again, exiting.");
					}
					String rc = "3";
					stats = d.statsExist();
					if(stats > 0){
						output.setText(processStats);
						//rc = CONSOLE_INPUT.nextLine().strip();
					}
						
				}
			}
			});
		innerAdd.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				innerAdd.setVisible(false);
				secInnerAdd.setVisible(true);

				//newDataID = CONSOLE_INPUT.nextLine().strip();
				newDataID = inputT.getText();
					if (!(dh.checkID(newDataID))){
						//System.out.println("For new " + newDataID + " collection, what is the source file name?\n");
						output.setText("For new " + newDataID + " collection, what is the source file name?");

					}else{
						secInnerAdd.setVisible(false);
						//System.out.println(newDataID + " is in the current database, displaying existing statistics.\n");
						output.setText("" + newDataID + " is in the current database. Please return home or exit.");
					}
			}
			});
		secInnerAdd.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				secInnerAdd.setVisible(false);
				innerSearch.setVisible(true);
				//final String input = CONSOLE_INPUT.nextLine().strip();
				final String input = inputT.getText();
				boolean check = dh.addCollection(newDataID,input);
				if(check) {
					//System.out.println("Collection " + newDataID + " added\n");
					output.setText("Collection " + newDataID + " added");
					found = true;

					if (found){
						final String processStats = newDataID + ": statistics are already computed and saved \n"
							+ "Choose one of the following functions:\n\n"
							+ "\t 3. Use existing stat data.\n" 
							+ "\t 4. Process statistics again, I have new data.\n";
					
						try{
							d = dh.populateCollection(newDataID);
						}
						catch(IOException ee){
							output.setText("Dataset path not found: " + ee.getMessage() + " Please check the file and try again, exiting.");
						}
						rc = "3";
						int stats = d.statsExist();
						if(stats > 0){
							//System.out.println(processStats);
							output.setText(processStats);
							//rc = CONSOLE_INPUT.nextLine().strip();
						}
						
					}
				}
				else {
					//System.out.println("File not found.");
					//System.out.println("Try again.");
					output.setText("File not found. Try again.");
				}
			}
			});
		innerSearch.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				innerSearch.setVisible(false);
				rc = inputT.getText();
				if (rc.contains("4") || (stats == 0)) {
					//System.out.println("Computing...");
					output.setText("Computing...");
					d.computeStats();
					//if stats were computed again, save them.
					dh.saveStats(newDataID);
					try{
						dh.saveDB();
					}
					catch(IOException ee){
						output.setText("Dataset path not found: " + ee.getMessage() + " Please check the file and try again, exiting.");
					}
				}

				//this blocks processes computed statistics in dh
				int k = 20;
				//prints report to file and console 
				output.setText(dh.printReport(newDataID,k));
				
			}
			});
	}
	
    public static void main(final String [] args) {

		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				RatingStatsApp app = new RatingStatsApp("Rating Stats App");
				app.setVisible(true);
				
			}
		});
		
	}
}
