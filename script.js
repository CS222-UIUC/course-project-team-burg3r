function menuToggle() {
    document.getElementById("dropdown").classList.toggle("show");
}

function addCourse() {
    var course = {
        subject: document.getElementById("subject").value,
        number: document.getElementById("number").value
    };
            
    // currently just displays the value added (to change)
    alert(JSON.stringify(course));
}

function submitCourses() {
    var courses = document.getElementsByClassName("course")

    // currently just displays all courses added (to change)
    alert(JSON.stringify(courses));
}

window.onclick = function(event) {
    if (!event.target.matches('.dropbtn')) {
        var dropdowns = document.getElementsByClassName("dropdown-content");
        var i;
        for (i = 0; i < dropdowns.length; i++) {
        var openDropdown = dropdowns[i];
        if (openDropdown.classList.contains('show')) {
            openDropdown.classList.remove('show');
        }
        }
    }
}

let weather = {
    "apiKey": "463a026d4300064311c0be34302d7697",
    fetchWeather: function (city) {
      fetch(
        "https://api.openweathermap.org/data/2.5/weather?q="
        + city
        + "&units=imperial&appid=463a026d4300064311c0be34302d7697"
      )
      .then((response) => response.json())
      .then((data) => this.displayWeather(data));
    },
    displayWeather : function(data) {
      const { name } = data;
      const { icon, description } = data.weather[0];
      const { temp, humidity } = data.main;
      const { speed } = data.wind;
      console.log(name, icon, description, temp, humidity, speed)
      document.querySelector(".city").innerText = "Weather in " + name;
      document.querySelector(".icon").src = "https://openweathermap.org/img/wn" + icon + "@2x.png";
      document.querySelector(".description").innerText = description;
      document.querySelector(".temp").innerText = temp + "°F";
      document.querySelector(".humidity").innerText = "Humidity: " + humidity + "%";
      document.querySelector(".wind").innerText = "Wind speed: " + speed + " mph";
  },
  search: function() {
    this.fetchWeather(document.querySelector(".search-bar").value);
  }
};

document
  .querySelector(".search button")
  .addEventListener("click", function() {
    weather.search();
})