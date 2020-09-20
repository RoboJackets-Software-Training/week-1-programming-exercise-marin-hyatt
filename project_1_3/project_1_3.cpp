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
  //pack with zeros!

  //first, calculate how many zeroes to add at beginning and end
  int num_zeros = (w.size() - 1) / 2;

  //create adjusted vector with space for zero padding at beginning and end
  std::vector<double> x_adjusted(x.size() + 2 * num_zeros);
  std::cout << x.size() + 2 <<std::endl;

  //set first and last elements to 0
  for (int count = 0; count < num_zeros; count++) {
    x_adjusted[count] = 0;
    x_adjusted[x_adjusted.size() - (count + 1)]= 0;
  }

  //test print x_adjusted
  std::cout << "x_adjusted: ";
  for (double i : x_adjusted) {
    std::cout << i << " ";
  }
  std::cout << "x_adjusted size: " << x_adjusted.size() <<std::endl;

  //deep copy of x goes in the middle 
  for (int i = 0; i < x.size(); i++) {
    x_adjusted[i + num_zeros] = x[i];
  }
  
  //test print x_adjusted
  std::cout << "x_adjusted: ";
  for (double i : x_adjusted) {
    std::cout << i << " ";
  }
  std::cout << "x_adjusted size: " << x_adjusted.size() <<std::endl;

  // //start filling in elements of y
  // for (int i = num_zeros; i < x.size() + num_zeros; i++) {
  //   y.push_back(x_adjusted[i-1] * w[0] + x_adjusted[i] * w[1] + x_adjusted[i+1] * w[2]);
  // }

  //start filling in elements of y
  for (int count = 0; count < x.size(); count++) {
    //for each element in the kernel:
    double y_element = 0;
    for (int j = 0; j < w.size(); j++) {
      y_element += (x_adjusted[j + count] * w[j]);
    }
    y.push_back(y_element);
  }

  //print y
  for (double i : y) {
    std::cout << i << " ";
  }
  // =========== END ===========

  return 0;
}

