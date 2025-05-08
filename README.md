![avl-product-ranker](logo.png)

<div align="center">
  <h1>Avl Product Ranker</h1>
  <p>A specialized data structure optimized for efficient product management based on quality and time attributes. The structure utilizes two AVL trees working in tandem to provide optimal time complexity for various operations.</p>

  <!-- Badges -->
  <p>
    <img src="https://img.shields.io/github/languages/top/orishlach/avl-product-ranker?color=red" alt="language" />
    <img src="https://img.shields.io/github/languages/code-size/orishlach/avl-product-ranker?color=informational" alt="code size" />
  </p>
  
<!-- Links -->
  <h4>
    <a href="#program-interface">Program Interface</a>
    <span> · </span>
    <a href="#setup--installation">Installation</a>
    <span> · </span>
    <a href="#primary-components" target="_blank">Primary Components</a>
  </h4>
  <p>
    <small align="justify">
      Built with 🤍 by 
      <a href="https://github.com/orishlach">Or Ishlach</a> 
    </small>
  </p>
</div><br/>
 


### Primary Components

#### 1. Quality-Keyed AVL Tree
- Nodes sorted by quality key with time as the stored value
- Each node links to a sub-AVL tree containing duplicates (same quality, different times)
- Rank calculation includes all duplicates in the subtree
- Flag field indicates subtree status (1 = subtree node, 0 = main tree node)

#### 2. Time-Keyed AVL Tree
- Nodes sorted by time key with quality as the stored value
- No duplicates allowed (time is unique)
- Direct mapping between time and quality values

### Additional Fields
- **Special Quality**: Designated quality value for tracking purposes
- **Special Quality Flag**: Boolean indicator (1 = product with special quality exists, 0 = no special quality products)

### Visual Representation

```
┌──────────────────────────────────────────────────────┐
│                Main Data Structure (DS)              │
└───────────────────────────┬──────────────────────────┘
                            │
          ┌─────────────────┴────────────────┐
          │                                  │
┌─────────▼────────────┐         ┌───────────▼─────────┐
│ AVL Tree by Quality  │         │  AVL Tree by Time   │
└─────────┬────────────┘         └───────────┬─────────┘
          │                                  │
          │                                  │
┌─────────▼────────────┐         ┌───────────▼─────────┐
│       (q1,t1)        │         │        (t1,q1)      │
│       (q2,t3)        │         │        (t2,q1)      │
└─────────┬────────────┘         │        (t3,q2)      │
          │                      └─────────────────────┘
          │
┌─────────▼────────────┐
│ Time-sorted subtree  │
│      for q1:         │
│     (q1,t1)          │
│     (q1,t2)          │
└──────────────────────┘
```

**Detailed Structure of Trees:**

```
   Quality Tree                    Time Tree
       (q1)                          (t1)
      /    \                        /    \
    (-)    (q2)                  (-)    (t2)
     |                                   / \
   (q1,t1)                             (-) (t3)
    /   \
 (q1,t1)(q1,t2)
```



## Setup & Installation

To compile the program, use the following command:

```bash
gcc avl.c -o program
```

### Execution
Run the compiled program:

```bash
./program
```

## Program Interface
When you run the program, you'll see an interface like this:

```
Enter the SPECIAL quality value (s): 5
========== PRODUCT MENU ==========
1. Add product
2. Remove product by time    
3. Remove products by quality
4. Get i-th rank product     
5. Get i-th rank product between times
6. Does special quality exist?
0. Exit
Choose:
```


#### `Init(int s)`
- **Purpose**: Initialize the data structure
- **Parameters**: `s` - special quality value to track
- **Actions**:
  - Create empty AVL trees
  - Set special quality field
- **Returns**: Initialized data structure
- **Time Complexity**: O(1)

#### `AddProduct(DataStructure* ds, int time, int quality)`
- **Purpose**: Add a new product to the system
- **Parameters**: 
  - `ds` - pointer to data structure
  - `time` - unique time identifier
  - `quality` - quality rating
- **Actions**:
  - Check special quality status
  - Add to time-sorted AVL tree
  - Add to quality-sorted tree and subtree
- **Time Complexity**: O(log n)

#### `RemoveProduct(DataStructure* ds, int time)`
- **Purpose**: Remove product by its time value
- **Parameters**:
  - `ds` - pointer to data structure
  - `time` - time identifier to remove
- **Actions**:
  - Locate product in time tree
  - Remove from quality tree/subtree
  - Update special quality flag if needed
- **Time Complexity**: O(log n)

#### `RemoveQuality(DataStructure* ds, int quality)`
- **Purpose**: Remove all products of a specific quality
- **Parameters**:
  - `ds` - pointer to data structure
  - `quality` - quality value to remove
- **Actions**:
  - Update special quality flag if needed
  - Remove all matching products from both trees
- **Time Complexity**: O(k·log n)

#### `GetIthRankProduct(DataStructure ds, int i)`
- **Purpose**: Retrieve the ith product by rank
- **Parameters**:
  - `ds` - data structure
  - `i` - rank to retrieve
- **Actions**: Binary-search through trees using rank information
- **Returns**: Time value of ith ranked product, or -1 if not found
- **Time Complexity**: O(log n)

#### `GetIthRankProductBetween(DataStructure ds, int time1, int time2, int i)`
- **Purpose**: Find the ith product within a time range
- **Parameters**:
  - `ds` - data structure
  - `time1` - start of time range
  - `time2` - end of time range
  - `i` - rank within range
- **Returns**: Time value of ith product in range, or -1 if not found
- **Time Complexity**: O(i·log n)

#### `Exists(DataStructure ds)`
- **Purpose**: Check if a product with special quality exists
- **Parameters**: `ds` - data structure
- **Returns**: 1 if exists, 0 otherwise
- **Time Complexity**: O(1)

## Time Complexity Analysis

| Operation | Average Case | Worst Case | Notes |
|-----------|--------------|------------|-------|
| Init | O(1) | O(1) | Constant time initialization |
| AddProduct | O(log n) | O(log n) | Standard AVL tree insertion |
| RemoveProduct | O(log n) | O(log n) | Standard AVL tree deletion |
| RemoveQuality | O(k·log n) | O(n·log n) | k = number of products with given quality |
| GetIthRankProduct | O(log n) | O(log n) | Uses binary search approach |
| GetIthRankProductBetween | O(i·log n) | O(i·log n) | i = rank within range |
| Exists | O(1) | O(1) | Direct flag access |
