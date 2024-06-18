package eu.deic.ase;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Client {

	public static void main(String[] args) {
		
		Building b1 = new Building(23, 300, "LA", LocalDate.now());
		Building b2 = new Building(43, 200, "CA", LocalDate.parse(new String("2023-02-02")));
		Building b3 = new Building(73, 350, "NY", LocalDate.now());
		Building b4 = new Building(34, 633, "LA", LocalDate.parse(new String("2026-03-03")));
		Building b5 = new Building(83, 455, "MI", LocalDate.now());
		Building b6 = new Building(15, 735, "CS", LocalDate.parse(new String("2025-03-07")));
		List<Building> listInsert = new ArrayList<Building>(Arrays.asList(b1,b2,b3,b4,b5,b6));
		Plans p1 = new Plans("INSERT",listInsert);
		List<Building> listUpdate = new ArrayList<Building>(Arrays.asList(b3,b5));
		Plans p2 = new Plans("UPDATE",listUpdate);
		List<Building> listDelete = new ArrayList<Building>(Arrays.asList(b3,b6));
		Plans p3 = new Plans("DELETE",listDelete);
		try(Socket client = new Socket("localhost",2333)){
			ObjectOutputStream os = new ObjectOutputStream(client.getOutputStream());
			
			os.writeObject(p1);
			os.writeObject(p2);
			os.writeObject(p3);
			os.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	
	}

}
