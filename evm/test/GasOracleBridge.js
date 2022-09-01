const {
    time,
    loadFixture,
} = require("@nomicfoundation/hardhat-network-helpers");
const { anyValue } = require("@nomicfoundation/hardhat-chai-matchers/withArgs");
const { expect } = require("chai");

const GAS_PRICE = 23610503242;

describe("GasOracleBridge", function () {
    // We define a fixture to reuse the same setup in every test.
    // We use loadFixture to run this setup once, snapshot that state,
    // and reset Hardhat Network to that snapshot in every test.
    async function deployFixture() {
        // Contracts are deployed using the first signer/account by default
        const [owner, otherAccount] = await ethers.getSigners();

        const OracleBridge = await ethers.getContractFactory("GasOracleBridge");
        const bridge = await OracleBridge.deploy(owner.address, GAS_PRICE);

        return { bridge, owner, otherAccount};
    }

    describe("Deployment", function () {
        it("Should set the gas price", async function () {
            const { bridge, owner, otherAccount } = await loadFixture(deployFixture);
            await expect(await bridge.gasPrice()).to.equal(GAS_PRICE);
        });
    });
    describe("Configuration", function () {
        it("Should let native bridge evm address set the gas price", async function () {
            const { bridge, owner, otherAccount } = await loadFixture(deployFixture);
            await expect(bridge.setPrice(11111)).to.not.be.reverted;
            await expect(await bridge.gasPrice()).to.equal(11111);
        });
        it("Should not let any other account  set the gas price", async function () {
            const { bridge, owner, otherAccount } = await loadFixture(deployFixture);
            await expect(bridge.connect(otherAccount).setPrice(11111)).to.be.reverted;
        });
    });
});