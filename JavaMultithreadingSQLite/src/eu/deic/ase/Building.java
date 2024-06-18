package eu.deic.ase;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.Objects;

public class Building implements Serializable, Cloneable{
	
	private static final long serialVersionUID = 1L;
	private int heigth;
    private int cost;
    private String city;
    private LocalDate openday;
    
 
    
    public Building(int height, int cost, String city, LocalDate openDay) {
    	this.heigth = height;
    	this.cost = cost;
    	this.city = city;
    	this.openday = openDay;
    }

	public int getHeigth() {
		return heigth;
	}
	public void setHeigth(int heigth) {
		this.heigth = heigth;
	}
	public int getCost() {
		return cost;
	}
	public void setCost(int cost) {
		this.cost = cost;
	}
	public String getCity() {
		return city;
	}
	public void setCity(String city) {
		this.city = city;
	}
	public LocalDate getOpenday() {
		return openday;
	}
	public void setOpenday(LocalDate openday) {
		this.openday = openday;
	}
	

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Building other = (Building) obj;
		return  Objects.equals(city, other.city) && cost == other.cost
				&& heigth == other.heigth && Objects.equals(openday, other.openday);
	}

	@Override
	protected Building clone() throws CloneNotSupportedException {
		Building b = (Building) super.clone();
		
		Building deepCopy = new Building(b.getHeigth(), b.getCost(), b.getCity(), b.getOpenday());
		return deepCopy;
	}

	@Override
	public String toString() {
		return "Building details - " + heigth + "," + cost + "," + city + "," + openday;
	}
    
    
    
}

