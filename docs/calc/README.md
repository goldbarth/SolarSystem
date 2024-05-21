## Celestial body property calculations

*Disclaimer: The calculations are adapted for the simulation model in order to be able to implement the ratio in a simplified manner.*


#### Celestial body scales:

Scaling calculation when Mercury has a scale of 1 as the entry point.

`Celestial body scale = diameter celestial body / diameter mercury`

- Sun: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 284,84 (1.390.000 km)
- Mercury: &nbsp; 1,00 (4.880 km)
- Venus: &nbsp;&nbsp;&nbsp;&nbsp; 2,48 (12.104 km)
- Earth: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 2,61 (12.742 km)
- Moon:	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 0,71 (3.476 km)
- Mars: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 1,39 (6.779 km)
- Jupiter: &nbsp;&nbsp;&nbsp; 28,65 (139.820 km)
- Saturn: &nbsp;&nbsp;&nbsp; 23,86 (116.460 km)
- Uranus: &nbsp;&nbsp; 10,39 (50.724 km)
- Neptune: &nbsp;10,09 (49.244 km)


---------------------------------------------------------------------

#### Distance of the celestial bodies to the sun:

Position calculation (UU = unreal unit, AU = astronomical unit)

Sun values:

`Sun diameter in UU = 100UU * 284,84 = 28.484 UU`

`Sun radius in UU = 14.242 UU`

`Celestial body distance = sun radius + (celestial body AU * 100)`

On the Y axis:

- Mercury: 390 UU (0,39 AU) = 53242,0
- Venus: &nbsp;&nbsp; 720 UU (0,72 AU) = 86242,0,0
- Earth: &nbsp;&nbsp;&nbsp; 1.000 UU (1,00 AU) = 114242,0
- Mars:	&nbsp;&nbsp;&nbsp;&nbsp; 1.520 UU (1,52 AU) = 166242,0
- Jupiter: &nbsp;&nbsp; 5.200 UU (5,20 AU) = 534242,0
- Saturn: &nbsp;&nbsp; 9.580 UU (9,58 AU) = 972242,0
- Uranus: &nbsp; 19.220 UU (19,22 AU) = 1936242,0
- Neptune: 30.050 UU (30,05 AU) = 3019242,0

Example start location: Sun (0, 0, 0) and Mars location (0, 166242.0, 0)

---------------------------------------------------------------------

#### Celestial body masses:

Mass calculation when earth has a mass of 1000 kg and the sun 332.946.000 kg as the entry point.

Earth mass = 1 Unit (EU)

`Celestial body mass (BM) = celestial body mass / sun mass`

`Mass of celestial bodies in relation to the sun = EU * BM`

- Sun: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 332.946.000 kg
- Mercury: &nbsp; 55 kg
- Venus: &nbsp;&nbsp;&nbsp;&nbsp; 815 kg
- Earth: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 1.000 kg
- Moon:	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 12,3 kg
- Mars: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 107 kg
- Jupiter: &nbsp;&nbsp;&nbsp; 317.800 kg
- Saturn: &nbsp;&nbsp;&nbsp; 95.200 kg
- Uranus: &nbsp;&nbsp; 14.500 kg
- Neptune: &nbsp; 17.100 kg

---------------------------------------------------------------------

#### Celestial body initial velocities:

- Sun: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 0 m/s
- Mercury: &nbsp; 21,5 km/s
- Venus: &nbsp;&nbsp;&nbsp;&nbsp; 19,0 km/s
- Earth: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 16,7 km/s
- Moon:	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; TBA
- Mars: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 14,6 km/s
- Jupiter: &nbsp;&nbsp;&nbsp; 8,6 km/s
- Saturn: &nbsp;&nbsp;&nbsp; 6,0 km/s
- Uranus: &nbsp;&nbsp; 4,0 km/s
- Neptune: &nbsp; 3,3 km/s

---------------------------------------------------------------------

### Sources: 

Data:
- en: https://solarviews.com/eng/data2.htm
- de: https://solarviews.com/germ/data2.htm

Orbits:
- https://science.nasa.gov/solar-system/