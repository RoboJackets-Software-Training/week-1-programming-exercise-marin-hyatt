#include <iostream>
#include <vector>

std::vector<double> readInVector(std::string s) {
  int prev_location = 0;
  int next_location = 0;
  std::vector<double> result;
  while(s.find(',', prev_location) != std::string::npos) {
    next_location = s.find(',', prev_location);
    //std::cout << "prev_location: " << prev_location << std::endl;
    //std::cout << "next_location: " << next_location << std::endl;
    // substr [,]
    //std::cout << s.substr(prev_location, next_location - prev_location) << std::endl;
    result.push_back(std::stod(s.substr(prev_location, next_location - prev_location)));
    next_location++;
    prev_location = next_location;
  }
  result.push_back(std::stod(s.substr(prev_location, std::string::npos)));
  return result;
}

int main() {
  std::vector<double> x;
  std::vector<double> w;
  std::vector<double> y;
  bool pack_with_zeros = true;

  std::string s;
  std::cin >> s;
  if(s == "false") {
    pack_with_zeros = false;
  }
  std::cin >> s;
  x = readInVector(s);
  std::cin >> s;
  w = readInVector(s);
  // TODO write your code here
  // =========== START =========
  //first, calculate how many zeroes or other numbers to add at beginning and end
    int num_zeros = (w.size() - 1) / 2;

    //create adjusted vector with space for padding at beginning and end
    std::vector<double> x_adjusted(x.size() + 2 * num_zeros);
    std::cout << x.size() + 2 <<std::endl;

    //set first and last elements to either 0 or closest element of x
    for (int count = 0; count < num_zeros; count++) {
      if (pack_with_zeros) {
        x_adjusted[count] = 0;
        x_adjusted[x_adjusted.size() - (count + 1)]= 0;
      } else {
        x_adjusted[count] = x[0];
        x_adjusted[x_adjusted.size() - (count + 1)]= x[x.size() - 1];
      }
    }

    //deep copy of x goes in the middle 
    for (int i = 0; i < x.size(); i++) {
      x_adjusted[i + num_zeros] = x[i];
    }

    //start filling in elements of y
    for (int count = 0; count < x.size(); count++) {
      //for each element in the kernel:
      double y_element = 0;
      for (int j = 0; j < w.size(); j++) {
        y_element += (x_adjusted[j + count] * w[j]);
      }
      y.push_back(y_element);
    }

    //print x
    std::cout << "x: {";
    for (double i = 0; i < x.size(); i++) {
      std::cout << x[i];
      if (i < x.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "}" << std::endl;

    //print w
    std::cout << "w: {";
    for (double i = 0; i < w.size(); i++) {
      std::cout << w[i];
      if (i < w.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "}" << std::endl;

    //print y
    std::cout << "{";
    for (double i = 0; i < y.size(); i++) {
      std::cout << y[i];
      if (i < y.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "}" << std::endl;

  // =========== END ===========

  return 0;
}

