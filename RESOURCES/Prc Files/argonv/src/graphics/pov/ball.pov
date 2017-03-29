// Persistence Of Vision raytracer version 3.1	sample file.
// File by Alexander Enzmann

global_settings { assumed_gamma 2.2 }

camera {
   location  <0, 0, -8>
   direction <0, 0, 1.2071>
   look_at   <0, 0, 0>
}

background { color red 3 green 3 blue 3 }

object {
  union {

	sphere { <0.0, 0.0, 0.0>, 3
           finish { ambient .1 diffuse 1.3 phong 1 }
   	   pigment { color red .7 green .7 blue .7 }
	}
   }


   scale <1.33, 1, 1>
}

light_source { <-10, 10, -20> color red 1 green 1 blue 1 }
