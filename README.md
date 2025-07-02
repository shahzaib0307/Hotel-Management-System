# Project Report

## HOTEL MANAGEMENT SYSTEM

### Team Members:
- **Muhammad Suffian Khan** (K23-0929)  
- **Zain Khan** (K24-0509)  
- **Musab Ali** (K24-0528)  
- **Shahzaib Hasan** (K24-0584)  

### Submitted to:
**Mr. Shaheer Ahmed Khan**

---

## Introduction

This project is a **Hotel Management System** implemented in the **C programming language**. It aims to streamline hotel operations, including:
- User authentication  
- Room booking  
- Food ordering  
- Checkout processes  

The program is designed for educational purposes, demonstrating the use of basic **file handling**, **structured programming**, and **menu-driven interaction**.

---

## Objectives
- Automate user authentication and account management.
- Provide real-time room availability and booking functionality.
- Allow seamless room switching and food ordering.
- Generate a detailed billing system for checkout.

---

## Technologies Used
- **C Language** for core programming logic.
- **File Handling** for storing and retrieving user and booking data.
- **Console Interface** with a menu-driven approach for user interaction.

---

## System Design

### Functional Modules

1. **User Management**:
   - Login and account creation with validation against stored records.
   - Authentication checks based on username-password pairs stored in `records.txt`.

2. **Room Management**:
   - Displays available rooms based on data in `roombooking.txt`.
   - Allows booking, changing rooms, and updating availability in files.

3. **Food Ordering**:
   - Displays three food deals with predefined costs.
   - Updates food charges in the `hotelrecord.txt`.

4. **Checkout**:
   - Reads user data, calculates total charges, and removes the user’s data upon checkout.

---

## Functionality Overview
- **`checkUser()` and `createUser()`**:
  Handles user authentication and account creation. Validates inputs against stored records.

- **`availableRooms()`**:
  Reads `roombooking.txt` to display unbooked rooms.

- **`bookRoom()`**:
  Books a room, updates availability, and logs booking data in `hotelrecord.txt`.

- **`changeRoom()`**:
  Allows users to switch rooms, updating room availability and user records.

- **`foododering()`**:
  Calculates food charges based on the chosen meal plan and updates the user’s record.

- **`checkOut()`**:
  Finalizes the user’s stay, generates a bill, and removes the user from the records.

---

## Implementation Details

The system is implemented using the **C language** with file-based data storage. It employs:
- `records.txt` for authentication.
- `roombooking.txt` for tracking room availability.
- `hotelrecord.txt` for maintaining user bookings and charges.

Key functionalities include:
- Room booking
- Food ordering
- Check-out  

These processes include real-time updates to the above files using standard I/O functions (`fopen`, `fgets`, `fprintf`). Room and user data are processed through arrays and structs for efficient management.

---

## Future Enhancements
- Add **GUI support** for better user interaction.
- Implement **database integration** for scalable data management.
- Add room filtering based on **amenities** or **price range**.
- Include **payment gateway simulation** for secure transactions.

---

## Wrap Up

The **Khan Hotel Management System** successfully demonstrates the core functionalities of hotel management using **file handling** in C. The project serves as a foundation for more advanced systems with enhanced features.

---

### Course:
**CL1002 - Programming Fundamentals (Lab)**
