package eu.deic.ase;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Plans implements Serializable {

	private static final long serialVersionUID = 1L;
	private String action;
	List<Building> actives;
	
	public Plans(String action) {
		this.action = action;
	}
	
	public Plans(String action, List<Building> actives) {
	    this.action = action;
	    this.actives = actives;
	}
	
	public List<Building> getActives() {
		return actives;
	}
	public void setActives(List<Building> actives) {
		this.actives = actives;
	}
	public String getAction() {
		return action;
	}
	public void setAction(String action) {
		this.action = action;
	}



	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Plans other = (Plans) obj;
		return Objects.equals(action, other.action) && Objects.equals(actives, other.actives);
	}

	@Override
	protected Object clone() throws CloneNotSupportedException {
		Plans p = (Plans) super.clone();
		List<Building> acvs = new ArrayList<>();
		for(Building b : p.getActives()) {
			acvs.add(b.clone());
		}
		
		Plans deepCopy = new Plans(p.getAction(), acvs);
		
		return deepCopy; 
	}

	@Override
	public String toString() {
		return "Plans [action=" + action + ", actives=" + actives + "]";
	}

	
}

