package eu.deic.ase;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.time.LocalDate;

public class Server {

	private static Connection c;
	private static String cClass = "org.sqlite.JDBC";
	private static String connectivityString = "jdbc:sqlite:test:db";
	private static int index = 1;
	
	public static void initConnection() throws ClassNotFoundException, SQLException {
		Class.forName(cClass);
		c = DriverManager.getConnection(connectivityString);
		c.setAutoCommit(false);
	}
	
	public static void create() throws SQLException {
		Statement st = c.createStatement();
		
		st.executeUpdate("drop table if exists BUILDINGS");
		st.executeUpdate("create table BUILDINGS(ID INT PRIMARY KEY NOT NULL, HEIGHT INT, COST INT, CITY TEXT, OPENDAY DATE)");
		
		st.close();
		c.commit();
	}
	
	public static void insert(Plans p) throws SQLException {
		PreparedStatement ps = c.prepareStatement("insert into BUILDINGS(ID,HEIGHT,COST,CITY,OPENDAY) values(?,?,?,?,?)");

		for(Building b : p.getActives()) {
			ps.setInt(1, index);
			ps.setInt(2, b.getHeigth());
			ps.setInt(3, b.getCost());
			ps.setString(4, b.getCity());
			ps.setDate(5, Date.valueOf(b.getOpenday()));
			index++;
			ps.executeUpdate();
		}
		
		ps.close();
		c.commit();
	}
	
	public static void select() throws SQLException {
		Statement st = c.createStatement();
		
		ResultSet sel = st.executeQuery("select * from BUILDINGS");
		while(sel.next()) {
			int id = sel.getInt("ID");
			int height = sel.getInt("HEIGHT");
			int cost = sel.getInt("COST");
			String city = sel.getString("CITY");
			Date openday = sel.getDate("OPENDAY");
			System.out.println("Building details - " + id + "," + height + "," + cost + "," + city + "," + openday);
		}
		
		st.close();
	}
	
	public static void update(Plans p) throws SQLException {
		PreparedStatement ps = c.prepareStatement("UPDATE BUILDINGS set OPENDAY = ?");
		
		for(Building b : p.getActives()) {
			ps.setDate(1, Date.valueOf(LocalDate.now()));
			ps.executeUpdate();
		}
		ps.close();
		c.commit();
	}
	
	public static void delete(Plans p) throws SQLException {
		PreparedStatement st = c.prepareStatement("delete from BUILDINGS where CITY = ?");
		
		for(Building b : p.getActives()) {
			st.setString(1,b.getCity());
			st.executeUpdate();
		}
		
		
		st.close();
		c.commit();
		
	}
	
	public static void closeConn() throws SQLException {
		if(c!=null) {
			c.close();
			c = null;
		}
	}
	
	public static void proccesActions(Socket client)throws SQLException {

		try(ObjectInputStream is = new ObjectInputStream(client.getInputStream())){

			Plans p = (Plans) is.readObject();
			System.out.println(p.getAction());
			if(p.getAction().equalsIgnoreCase("insert")) {
				initConnection();
				create();
				insert(p);
				select();
				closeConn();
			}
			Plans p1 = (Plans) is.readObject();
			System.out.println(p1.getAction());
			if(p1.getAction().equalsIgnoreCase("update")) {
				initConnection();
				update(p1);
				select();
				closeConn();
			}
			
			Plans p2 = (Plans) is.readObject();
			System.out.println(p2.getAction());
			if(p2.getAction().equalsIgnoreCase("delete")) {
				initConnection();
				delete(p2);
				select();
				closeConn();
			}
			
		} catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
		}

	}
	public static void main(String[] args) throws IOException {
		try(ServerSocket server = new ServerSocket(2333)){
			System.out.println("Server is listening in port 2333");
			while(true) {
				Socket client = server.accept();
				new Thread(() -> {
					try {
						proccesActions(client);
					} catch (SQLException e) {
						e.printStackTrace();
					}
				}).start();;
			}
		}
	}

}
