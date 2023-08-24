 using Counters for Counters.Counter;
    Counters.Counter private _tokenIds;

    address public owner;
    uint256 public cost;

    constructor(
        string memory _name,
        string memory _symbol,
        uint256 _cost
    ) ERC721(_name, _symbol) {
        owner = msg.sender;
        cost = _cost;
    }

    function mint(string memory tokenURI) public payable {
        require(msg.value >= cost);

        _tokenIds.increment();

        uint256 newItemId = _tokenIds.current();
        _mint(msg.sender, newItemId);
        _setTokenURI(newItemId, tokenURI);
    }

    function totalSupply() public view returns (uint256) {
        return _tokenIds.current();
    }

    function withdraw() public {
        require(msg.sender == owner);
        (bool success, ) = owner.call{value: address(this).balance}("");
        require(success);
    }












    test ??????????//

     let deployer, minter
  let nft

  const NAME = "AI Generated NFT"
  const SYMBOL = "AINFT"
  const COST = tokens(1) // 1 ETH
  const URL = "https://ipfs.io/ipfs/bafyreid4an6ng6e6hok56l565eivozra3373bo6funw3p5mhq5oonew6u4/metadata.json"

  beforeEach(async () => {
    // Setup accounts
    [deployer, minter] = await ethers.getSigners()

    // Deploy Real Estate
    const NFT = await ethers.getContractFactory('NFT')
    nft = await NFT.deploy(NAME, SYMBOL, COST)

    // Mint 
    const transaction = await nft.connect(minter).mint(URL, { value: COST })
    await transaction.wait()
  })

  describe('Deployment', () => {
    it('Returns owner', async () => {
      const result = await nft.owner()
      expect(result).to.be.equal(deployer.address)
    })

    it('Returns cost', async () => {
      const result = await nft.cost()
      expect(result).to.be.equal(COST)
    })
  })

  describe('Minting', () => {
    it('Returns owner', async () => {
      const result = await nft.ownerOf("1")
      expect(result).to.be.equal(minter.address)
    })

    it('Returns URI', async () => {
      const result = await nft.tokenURI("1")
      expect(result).to.be.equal(URL)
    })

    it('Updates total supply', async () => {
      const result = await nft.totalSupply()
      expect(result).to.be.equal("1")
    })
  })

  describe('Withdrawing', () => {
    let balanceBefore

    beforeEach(async () => {
      balanceBefore = await ethers.provider.getBalance(deployer.address)

      const transaction = await nft.connect(deployer).withdraw()
      await transaction.wait()
    })

    it('Updates the owner balance', async () => {
      const result = await ethers.provider.getBalance(deployer.address)
      expect(result).to.be.greaterThan(balanceBefore)
    })

    it('Updates the contract balance', async () => {
      const result = await ethers.provider.getBalance(nft.address)
      expect(result).to.equal(0)
    })
  })