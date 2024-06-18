package eu.deic.ase;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONTokener;

public class CitireJSON {

	public static void main(String[] args) throws FileNotFoundException, IOException, JSONException {
		try(FileReader file = new FileReader("lib/profesori.json")){
			JSONArray ja = new JSONArray(new JSONTokener(file));
			List<Profesor> list = new ArrayList<Profesor>();
			for(int i = 0; i < ja.length(); i++) {
				JSONObject json = ja.getJSONObject(i);
				int id = json.getInt("idProfesor");
				String prenume =  json.getString("prenume");
				String nume = json.getString("nume");
				String dep = json.getString("departament");
				Profesor p = new Profesor(id, prenume, nume, dep);
				list.add(p);
			}
			for(Profesor p : list)
				System.out.println(p);
			}	
		}
	}
